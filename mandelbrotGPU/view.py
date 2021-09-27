import numpy as np
from model import Model
from utils import SIZE, MAX_ITER, N_COLOR_VAR, mandel_gpu
import math
from numba import cuda
from timeit import default_timer as timer




class View:
    def __init__(self, model=Model):
        self.model = model
        self.camera_pos = [np.float64(0.0), np.float64(0.0)]
        self.zoom = np.float64(1.0)
        self.gpu_img = cuda.to_device(np.zeros(shape=(SIZE[1], SIZE[0], 3)))
        self.coloring_var = 0
        self.mandel_power = 2


    def construct_image(self):
        blockdim = (32, 8)
        griddim = (32, 16)

        start = timer()

        View.mandel_kernel[griddim, blockdim](self.gpu_img, MAX_ITER,
                                              self.camera_pos[0],
                                              self.camera_pos[1],
                                              self.zoom,
                                              self.coloring_var,
                                              self.mandel_power)
        dt = timer() - start

        print("Mandelbrot created on GPU in %f s" % dt)
        return self.gpu_img.copy_to_host()


    @staticmethod
    @cuda.jit
    def mandel_kernel(image, iters, cam_x, cam_y, zoom, coloring_var, mandel_power):
        width = image.shape[0]
        height = image.shape[1]

        startX, startY = cuda.grid(2)
        gridX = cuda.gridDim.x * cuda.blockDim.x
        gridY = cuda.gridDim.y * cuda.blockDim.y

        for x in range(startX, width, gridX):
            Re = ((x - SIZE[0] / 2) / (0.3 * zoom * SIZE[0]) + cam_x)
            for y in range(startY, height, gridY):
                Im = ((y - SIZE[1] / 2) / (0.3 * zoom * SIZE[1]) + cam_y)
                pixel_value = mandel_gpu(Re, Im, iters, mandel_power)
                #image[x, y, 0] = abs(int(pixel_value))
                #image[x, y, 1] = 0
                #image[x, y, 2] = int(abs(math.sin(pixel_value - 255) * 255))
                if coloring_var % N_COLOR_VAR == 0:
                    image[x, y, 0] = int(255 * (1 - math.cos(0.05 * pixel_value)) / 2)
                    image[x, y, 1] = int(255 * (1 - math.cos(0.3 * pixel_value)) / 2)
                    image[x, y, 2] = int(255 * (1 - math.cos(0.15 * pixel_value)) / 2)
                if coloring_var % N_COLOR_VAR == 1:
                    image[x, y, 0] = int(255 * (1 - math.sin(0.05 * pixel_value)) / 2)
                    image[x, y, 1] = int(255 * (1 - math.cos(0.3 * pixel_value)) / 2)
                    image[x, y, 2] = int(255 * (1 - math.cos(0.15 * pixel_value)) / 2)
                if coloring_var % N_COLOR_VAR == 2:
                    Zn = math.sqrt(Re * Re + Im * Im)
                    image[x, y, 0] = pixel_value + 50 - 50 * (math.log(2) / Zn ) / math.log(2)
                    image[x, y, 1] = pixel_value / 2 + 50 - 50 * (math.log(2) / (Zn*0.5) ) / math.log(2)
                    image[x, y, 2] = pixel_value + 50 - 50 * (math.log(2) / Zn ) / (0.8 * math.log(2))




