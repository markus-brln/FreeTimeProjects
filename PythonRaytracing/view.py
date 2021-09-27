import numpy as np
from model import Model
from utils import * #SIZE, gpu_mandel, gpu_distance2D, gpu_distance3D, gpu_angle, gpu_rotate_vector, rotate_vector
import math
from numba import cuda
from timeit import default_timer as timer


class View:
    def __init__(self, model):
        self.model = model
        self.cam_pos = self.model.cam_pos_init
        self.cam_rot = self.model.cam_rot_init
        self.zoom = np.float64(1.0)

        # x, y, rgb, given by pygame.surfarray.make_surface()
        self.gpu_img = cuda.to_device(np.zeros(shape=(SIZE[0], SIZE[1], 3)))

        self.coloring_var = 0


    def construct_image(self):
        blockdim = (32, 8)
        griddim = (32, 16)

        #start = timer()

        down = np.array([0.0, -1.0, 0.0])
        right = np.array([1.0, 0.0, 0.0])

        down = rotate_vector(down, self.cam_rot[0], self.cam_rot[1], 0.0)
        right = rotate_vector(right, self.cam_rot[0], self.cam_rot[1], 0.0)

        #down = normalize_vec(down[0], down[1], down[2])
        #right = normalize_vec(right[0], right[1], right[2])

        #print("cam_rot: ", self.cam_rot)
        #print("down right: ", down, right)
        cam_dir = np.cross(right, down)

        #print("right down cam: ", right, down, cam_dir)

        screen_centre = self.cam_pos + cam_dir * SIZE[1] * self.zoom

        #print("screen_centre: ", screen_centre)
        #print("cam rot: ", self.cam_rot)
        #print(down, right, cam_dir, screen_centre, type(screen_centre))

        #print(self.cam_pos, self.cam_dir, self.zoom, self.model.lights, self.model.objects)
        View.raytracing_kernel[griddim, blockdim](self.gpu_img,
                                                  cuda.to_device(self.cam_pos),
                                                  cuda.to_device(self.cam_rot),
                                                  self.zoom,
                                                  cuda.to_device(self.model.lights),
                                                  cuda.to_device(self.model.objects),
                                                  cuda.to_device(cam_dir),
                                                  cuda.to_device(down),
                                                  cuda.to_device(right),
                                                  cuda.to_device(screen_centre))

        #dt = timer() - start

        #print("Image created on GPU in %f s" % dt)
        return self.gpu_img.copy_to_host()

    @staticmethod
    @cuda.jit
    def raytracing_kernel(image, cam_pos, cam_rot, zoom, lights, objects, cam_dir, down, right, screen_centre):
        width = image.shape[0]
        height = image.shape[1]
        startX, startY = cuda.grid(2)
        gridX = cuda.gridDim.x * cuda.blockDim.x
        gridY = cuda.gridDim.y * cuda.blockDim.y

        for x in range(startX, width, gridX):
            for y in range(startY, height, gridY):
                pixel_x = screen_centre[0] + (x - SIZE[0] / 2) * right[0] + (y - SIZE[1] / 2) * down[0]
                pixel_y = screen_centre[1] + (x - SIZE[0] / 2) * right[1] + (y - SIZE[1] / 2) * down[1]
                pixel_z = screen_centre[2] + (x - SIZE[0] / 2) * right[2] + (y - SIZE[1] / 2) * down[2]
                #print(pixel_x, pixel_y, pixel_z)
                #pixel = [pixel_x, pixel_y, pixel_z]
                ray_dir = (pixel_x - cam_pos[0], pixel_y - cam_pos[1], pixel_z - cam_pos[2])
                ray_dir = gpu_normalize_vec(ray_dir[0], ray_dir[1], ray_dir[2])

                col_r, col_g, col_b = gpu_trace(cam_pos, ray_dir, lights, objects, RECURSION_DEPTH)

                #Ray ray(eye, (pixel - eye).normalized());
                #col = trace(ray, recursionDepth);
                image[x, y, :] = col_r, col_g, col_b  # x accessed before y by pygame.surfarray.make_surface (controller.run())


    # getters & setters


    def translate_cam(self, x, y, z):
        direction = (x, y, z)
        self.cam_pos += rotate_vector(direction, self.cam_rot[0], self.cam_rot[1], self.cam_rot[2])


    def rotate_cam(self, x, y, z):
        self.cam_rot[0] += x
        self.cam_rot[1] += y
        self.cam_rot[2] += z


    def multiply_zoom(self, factor):
        self.zoom *= factor

    def get_cam_pos(self):
        return self.cam_pos

    def get_cam_rot(self):
        return self.cam_rot

    def get_zoom(self):
        return self.zoom

    def set_cam_pos(self, new_pos):
        self.cam_pos = new_pos

    def set_cam_rot(self, new_rot):
        self.cam_rot = new_rot

    def set_zoom(self, new_zoom):
        self.zoom = new_zoom


