import numpy as np
from numba import cuda
from utils import *

class Model:
    def __init__(self, size_x, size_y, img):
        arr = np.zeros((size_x, size_y), dtype=np.uint8)
        #array[40:100][40:100] = 1
        #arr[2][2] = 1
        #arr[2][3] = 1
        #arr[2][4] = 1
        for x in range(len(img)):
            for y in range(len(img[0])):
                arr[x,y] = img[x,y]
        self.world1 = cuda.to_device(arr)
        self.world2 = cuda.to_device(arr)
        self.init_world = arr


    def reset_to_random_world(self):
        img = np.random.randint(low=0, high=2, size=(SIZE[0], SIZE[1]), dtype=np.uint8)
        img *= 255
        self.world1 = cuda.to_device(img)
        self.world2 = cuda.to_device(img)


    def reset_to_init_world(self):
        self.world1 = cuda.to_device(self.init_world)
        self.world2 = cuda.to_device(self.init_world)

        #self.upscaled_img = cuda.to_device(np.zeros((size_x * 2, size_y * 2)))

    @staticmethod
    @cuda.jit
    def time_step_sim(world1, world2, world1_active):
        width = world1.shape[0]
        height = world1.shape[1]

        startX, startY = cuda.grid(2)
        gridX = cuda.gridDim.x * cuda.blockDim.x
        gridY = cuda.gridDim.y * cuda.blockDim.y

        active_world = world1
        old_world = world2

        if not world1_active:
            active_world = world2
            old_world = world1

        # RULES:
        # If the cell is alive, then it stays alive if it has either 2 or 3 live neighbors
        # If the cell is dead, then it springs to life only in the case that it has 3 live neighbors

        for x in range(startX, width, gridX):
            for y in range(startY, height, gridY):
                n_neighbours = 0
                x_search_min = x - 1
                x_search_max = x + 2
                y_search_min = y - 1
                y_search_max = y + 2

                if x_search_min < 0:
                    x_search_min = 0
                if x_search_max > SIZE[0]:
                    x_search_max = SIZE[0]
                if y_search_min < 0:
                    y_search_min = 0
                if y_search_max > SIZE[1]:
                    y_search_max = SIZE[1]

                for x_search in range(x_search_min, x_search_max):
                    for y_search in range(y_search_min, y_search_max):
                        if not (x_search == x and y_search == y):
                            if old_world[x_search][y_search] == 255:
                                n_neighbours += 1

                if old_world[x][y] == 255:                  # treat as greyscale image
                    if n_neighbours == 2 or n_neighbours == 3:
                        active_world[x][y] = 255
                    else:
                        active_world[x][y] = 0

                if old_world[x][y] == 0:
                    if n_neighbours == 3:
                        active_world[x][y] = 255
                    else:
                        active_world[x][y] = 0



