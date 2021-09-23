import numpy as np
from model import Model
from utils import *
import math


class View:
    def __init__(self, model=Model):
        self.model = model
        self.camera_pos = np.zeros(3)
        self.camera_ang = np.zeros(3)
        self.zoom = 1


    @staticmethod
    def construct_image(image=np.array, iteration=float):
        pass