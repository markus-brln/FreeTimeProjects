import numpy as np
from utils import *


class Model:
    cam_pos_init = np.zeros(3)              # x,y,z position of camera
    cam_rot_init = np.zeros(3)              # rotation along x,y,z axes
    shadows = 0
    max_recursion_depth = 1

    def __init__(self, scene_path):
        self.scene_info = self.load_scene_info(scene_path)
        self.lights = self.load_lights(scene_path)
        self.objects = self.load_objects(scene_path)

    def load_scene_info(self, scene_path):
        # eye,    shadows_on, max_recursion_depth
        scene_info = np.array([0, 0, 0, 1, 1])

        return scene_info

    def load_lights(self, scene_path):
                        # [x, y,   z, R, G, B]
        light1 = np.array([0, 500, 0, 1, 1, 1])

        lights = [light1]
        raw_lights = [len(lights)]

        for light in lights:
            for data_point in light:
                raw_lights.append(data_point)

        raw_lights = np.array(raw_lights)

        return raw_lights

    def load_objects(self, scene_path):
        #triangle = np.ndarray([ObjectTypes.TRIANGLE,100, -100, -100, -100, -100, -100, -100, 100, -100])
        #gpu_triangle = cuda.to_device(triangle)
                        # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
        sphere1 = np.array([ObjectTypes.SPHERE.value, 0.5, 0.5, 0, 0.3, 0.3, 0.3, 1, 0, 50, 0, 0, -200])

        objects = [sphere1]

        raw_objects = [len(objects)]        # the first element of the array is the amount of objects in the scene

        for obj in objects:
            for data_point in obj:
                raw_objects.append(data_point)

        return np.array(raw_objects)


    def scene_info(self):
        return self.scene_info

    #def lights(self):
    #    return self.lights

    #def objects(self):
    #    return self.objets