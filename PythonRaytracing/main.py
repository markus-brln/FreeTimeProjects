from model import Model
from view import View
from controller import Controller


if __name__ == "__main__":
    model = Model("scenes/01_basic.json")

    view = View(model)

    controller = Controller(model, view)

    controller.run()

"""
Important resource that got me started with numba CUDA:
https://notebook.community/arasdar/DL/impl-dl/etc/misc3/numba-cuda-gpu-example

Making a single image from this tutorial was simply adapted to fit into my
MVC pattern template.


If no CUDA-enabled GPU is available, use CUDA-simulator:

Windows: SET NUMBA_ENABLE_CUDASIM=1

Linux/Mac: export NUMBA_ENABLE_CUDASIM=1

more info: https://nyu-cds.github.io/python-numba/05-cuda/ 
"""