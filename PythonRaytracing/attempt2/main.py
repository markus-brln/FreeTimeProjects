import logging
import pywavefront

from models.light import Light
from models.object import Obj

pywavefront.configure_logging(
    logging.DEBUG,
    formatter=logging.Formatter('%(name)s-%(levelname)s: %(message)s')
)


def parse_objects(object_names=None):
    if not object_names:
        object_names = ['cube1']
    object_list = []
    for name in object_names:
        wavefront_obj = pywavefront.Wavefront(f'objects/{name}/{name}.obj', collect_faces=True)
        # for wavefront_obj_name, material in wavefront_obj.materials.items():
        #     print(material.vertex_format)
        #     print(material.vertices)
        #     print(material.diffuse)
        #     print(material.ambient)
        #     print(material.texture)
        object_list.append(Obj(wavefront_obj))

    return object_list


def parse_lights():
    return [Light()]


if __name__ == '__main__':
    object_list = parse_objects()
    print(object_list)
