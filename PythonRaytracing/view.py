import numpy as np
from model import Model
from utils import SIZE, MAX_ITER, N_COLOR_VAR, mandel_gpu
import math
from numba import cuda
from timeit import default_timer as timer


class View:
    def __init__(self, model=Model):
        self.model = model
        self.cam_pos = self.model.cam_pos_init
        self.cam_dir = self.model.cam_dir_init
        print(self.cam_pos)

        self.zoom = np.float64(1.0)
        self.gpu_img = cuda.to_device(np.zeros(shape=(SIZE[1], SIZE[0], 3)))
        self.coloring_var = 0


    def construct_image(self):
        blockdim = (32, 8)
        griddim = (32, 16)

        start = timer()

        View.raytracing_kernel[griddim, blockdim](self.gpu_img,
                                                  cuda.to_device(self.cam_pos),
                                                  cuda.to_device(self.cam_dir),
                                                  self.zoom,
                                                  cuda.to_device(self.model.lights),
                                                  cuda.to_device(self.model.objects))

        dt = timer() - start

        print("Mandelbrot created on GPU in %f s" % dt)
        return self.gpu_img.copy_to_host()


    @staticmethod
    @cuda.jit
    def raytracing_kernel(image, cam_pos, cam_dir, zoom, lights, objects):
        width = image.shape[0]
        height = image.shape[1]

        startX, startY = cuda.grid(2)
        gridX = cuda.gridDim.x * cuda.blockDim.x
        gridY = cuda.gridDim.y * cuda.blockDim.y

        for x in range(startX, width, gridX):
            for y in range(startY, height, gridY):
                image[y, x, :] = 100





