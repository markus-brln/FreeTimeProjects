import numpy as np
from numba import cuda


def get_color(gpu_data_array, start_idx):
    return gpu_data_array[start_idx + 1], gpu_data_array[start_idx + 2], gpu_data_array[start_idx + 3]

def get_data_length():
    return 13

class Sphere:
    # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
    data_length = 13
    gpu_get_color = cuda.jit(device=True)(get_color)

