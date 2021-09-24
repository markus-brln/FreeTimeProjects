import numpy as np
from model import Model
from utils import SIZE, gpu_mandel, gpu_distance2D, gpu_distance3D, gpu_angle, gpu_rotate_vector, rotate_vector
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

        start = timer()

        down = np.array([0, -1, 0])
        right = np.array([1, 0, 0])
        down = rotate_vector(down, self.cam_rot[0], self.cam_rot[1], 0)
        right = rotate_vector(right, self.cam_rot[0], self.cam_rot[1], 0)

        cam_dir = np.cross(right, down)

        screen_centre = self.cam_pos + cam_dir * SIZE[1] * self.zoom
        print(down, right, cam_dir, screen_centre, type(screen_centre))

        # TODO send cam dir, down, right, screen centre to GPU
        #print(self.cam_pos, self.cam_dir, self.zoom, self.model.lights, self.model.objects)
        View.raytracing_kernel[griddim, blockdim](self.gpu_img,
                                                  cuda.to_device(self.cam_pos),
                                                  cuda.to_device(self.cam_rot),
                                                  self.zoom,
                                                  cuda.to_device(self.model.lights),
                                                  cuda.to_device(self.model.objects))

        dt = timer() - start

        print("Image created on GPU in %f s" % dt)
        return self.gpu_img.copy_to_host()


    @staticmethod
    @cuda.jit
    def raytracing_kernel(image, cam_pos, cam_rot, zoom, lights, objects):
        width = image.shape[0]
        height = image.shape[1]

        startX, startY = cuda.grid(2)
        gridX = cuda.gridDim.x * cuda.blockDim.x
        gridY = cuda.gridDim.y * cuda.blockDim.y

        for x in range(startX, width, gridX):
            for y in range(startY, height, gridY):
                image[y, x, :] = 100





