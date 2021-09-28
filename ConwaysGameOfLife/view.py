import numpy as np
from model import Model
from utils import *
from numba import cuda
import math


class View:
    def __init__(self, model=Model):
        self.model = model
        self.camera_pos = np.zeros(3)
        self.camera_ang = np.zeros(3)
        self.zoom = 1


    def construct_image(self, world1_active, progress_time):
        blockdim = (32, 8)
        griddim = (32, 16)
        #upscaled_img = cuda.to_device(np.zeros((SIZE[0] * 2, SIZE[1] * 2)))
        if progress_time:
            Model.time_step_sim[griddim, blockdim](self.model.world1, self.model.world2, world1_active)
        #Model.time_step_sim(self.model.world1, self.model.world2, world1_active)

        if world1_active:
            return self.model.world1.copy_to_host()
        else:
            return self.model.world2.copy_to_host()

