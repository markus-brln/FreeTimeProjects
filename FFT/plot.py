import math

import numpy as np
from matplotlib import pyplot as plt


def plot_np_arrays(array_list: list[np.ndarray]):
    dims = [round(math.sqrt(len(array_list)))] * 2
    if dims[0] * dims[1] < len(array_list):
        dims[1] += 1
    f, axarr = plt.subplots(dims[0], dims[1])
    for idx, arr in enumerate(array_list):
        if dims[0] < 2:
            if dims[1] < 2:
                axarr.plot(arr)
                continue
            axarr[math.floor(idx % dims[1])].plot(arr)
            continue
        axarr[math.floor(idx / dims[1])][math.floor(idx % dims[1])].plot(arr)
    plt.show()


def plot_np_images(image_list: list[np.ndarray]):
    dims = [round(math.sqrt(len(image_list)))] * 2
    if dims[0] * dims[1] < len(image_list):
        dims[1] += 1
    f, axarr = plt.subplots(dims[0], dims[1])
    for idx, image in enumerate(image_list):
        if dims[0] < 2:
            axarr[math.floor(idx % dims[1])].imshow(image)
            continue
        axarr[math.floor(idx / dims[1])][math.floor(idx % dims[1])].imshow(image)
    plt.show()
