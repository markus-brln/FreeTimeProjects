import numpy as np

from fft import fft, ifft
from plot import plot_np_arrays
from utils import read_mp3, write_mp3


def normalized_mean_deviation(x, y):
    if len(x) != len(y):
        raise ValueError(f'Arrays do not have the same length: {len(x)} {len(y)}')

    x = np.array(x)
    y = np.array(y)
    x = 2 * (x - np.min(x)) / np.ptp(x) - 1
    y = 2 * (y - np.min(y)) / np.ptp(y) - 1

    return np.mean(np.abs(x - y))


if __name__ == '__main__':
    frame_rate, arr = read_mp3('assets/Drum Origins - Again.mp3', merge_channels=True)

    arr = arr[45 * frame_rate:45 * frame_rate + 2**17]
    arr_fft = fft(arr)

    # arr_fft_cached = fft(arr, cached=True)
    compression_factor = 8
    arr_fft_zeros = np.copy(arr_fft)
    arr_fft_zeros[int(len(arr_fft_zeros) / compression_factor):] = 0
    arr_fft_zeros_other = np.copy(arr_fft)
    arr_fft_zeros_other[:-int(len(arr_fft_zeros_other) / compression_factor)] = 0
    arr_ifft = [elem * 2 for elem in ifft(arr_fft_zeros)]
    arr_ifft_other = [elem * 2 for elem in ifft(arr_fft_zeros_other)]

    print(normalized_mean_deviation(arr, arr_ifft))

    plot_np_arrays([arr, arr_fft, arr_fft_zeros, arr_ifft, arr_fft_zeros_other, arr_ifft_other])

    write_mp3('test_compressed.mp3', np.array(arr_ifft), frame_rate)
    write_mp3('test_compressed_other.mp3', np.array(arr_ifft_other), frame_rate)
    write_mp3('test.mp3', arr, frame_rate)
