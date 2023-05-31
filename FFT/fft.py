from cmath import exp, pi
from functools import cache

import numpy as np

from data_provider import basic_array, random_array, cos_array
from plot import plot_np_arrays
from utils import time_method, is_power_of_two


@time_method
def fft(x: list, cached=False):
    if not is_power_of_two(len(x)):
        raise ValueError(f'List length not a power of 2! It had len = {n}')

    def fft_rec(sub_arr: list):
        sub_arr = list(sub_arr)
        length = len(sub_arr)
        if length <= 1:
            return sub_arr

        even = fft_rec(sub_arr[0::2])
        odd = fft_rec(sub_arr[1::2])

        transform = [exp(-2j * pi * k / length) * odd[k] for k in range(length // 2)]

        return [even[k] + transform[k] for k in range(length//2)] + \
               [even[k] - transform[k] for k in range(length//2)]

    @cache
    def fft_rec_cached(sub_arr: tuple):
        sub_arr = list(sub_arr)
        length = len(sub_arr)
        if length <= 1:
            return sub_arr

        even = fft_rec_cached(tuple(sub_arr[0::2]))
        odd = fft_rec_cached(tuple(sub_arr[1::2]))

        transform = [exp(-2j * pi * k / length) * odd[k] for k in range(length // 2)]

        return [even[k] + transform[k] for k in range(length//2)] + \
               [even[k] - transform[k] for k in range(length//2)]

    return fft_rec_cached(tuple(x)) if cached else fft_rec(x)


def ifft(x, cached=True):
    """ use recursive method to speed up"""
    fu_conjugate = [np.conj(elem) for elem in x]

    fx = fft(fu_conjugate, cached)

    # conjugate every element and divide by length
    fx = [np.conj(elem) / len(fu_conjugate) for elem in fx]

    return fx


if __name__ == '__main__':
    # arr = basic_array(15)
    # arr = random_array(15, [0, 1])
    arr = cos_array(20)

    fft_result = fft(arr)
    fft_result2 = fft(arr, cached=True)
    # fft_inv_result = ifft(fft_result)

    plot_np_arrays([arr, fft_result])
    # plot_np_arrays([arr, fft_result, fft_inv_result])


