import numpy as np
from pywavefront import Wavefront

from models.triple import Triple


class Obj:
    v = np.ndarray([])  # vertices
    # vn = np.ndarray([])  # normals
    f = np.ndarray([])  # faces
    diffuse = np.asarray([0.64, 0.64, 0.64, 1.0])
    ambient = np.asarray([1.0, 1.0, 1.0, 1.0])

    def __init__(self, wavefront_obj: Wavefront):
        for wavefront_obj_name, material in wavefront_obj.materials.items():
            self.ambient = np.asarray(material.ambient)
            self.diffuse = np.asarray(material.diffuse)
        self.v = np.asarray([Triple(vertex) for vertex in wavefront_obj.vertices])
        self.f = np.asarray([Triple(vertex) for vertex in wavefront_obj.mesh_list[0].faces])


