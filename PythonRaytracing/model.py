import numpy as np
from utils import *


class Model:
    cam_pos_init = np.zeros(3)
    cam_dir_init = np.array([0, 0, -1])
    shadows = 0
    max_recursion_depth = 1

    def __init__(self, scene_path):
        self.scene_info = self.load_scene_info(scene_path)
        self.lights = self.load_lights(scene_path)
        self.objets = self.load_objects(scene_path)

    def load_scene_info(self, scene_path):
        # eye,    shadows_on, max_recursion_depth
        scene_info = np.array([0, 0, 0, 1, 1])

        return scene_info

    def load_lights(self, scene_path):
                       # [LIGHT,    R, G, B, x, y, z]
        light1 = np.array([ObjectTypes.LIGHT, 1, 1, 1, 0, 500, 0])

                        # n_lights, lights_data
        lights = [light1]

        raw_lights = [len(lights)]

        for light in lights:
            for data_point in light:
                raw_lights.append(data_point)

        raw_lights = np.array(raw_lights)

        return raw_lights

    def load_objects(self, scene_path):
        objects = list()
        #triangle = np.ndarray([ObjectTypes.TRIANGLE,100, -100, -100, -100, -100, -100, -100, 100, -100])
        #gpu_triangle = cuda.to_device(triangle)
                        # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
        sphere = np.array([ObjectTypes.SPHERE, 0.5, 0.5, 0, 0.3, 0.3, 0.3, 1, 0, 50, 0, 0, -200])

        # TODO do like for lights raw data
        #gpu_sphere = cuda.to_device(sphere)
        print(sphere)
        objects.append(sphere)

        return objects


    def scene_info(self):
        return self.scene_info

    #def lights(self):
    #    return self.lights

    #def objects(self):
    #    return self.objets