import time
from functools import wraps

import numpy as np
import pydub


def time_method(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start_time = time.perf_counter()
        result = func(*args, **kwargs)
        end_time = time.perf_counter()
        total_time = end_time - start_time
        print(f'Function {func.__name__} with kwargs: {kwargs} Took {total_time:.6f} seconds')
        return result
    return wrapper


def read_mp3(filename, normalized=False, merge_channels=False):
    """MP3 to numpy array"""
    audio_seg = pydub.AudioSegment.from_mp3(filename)
    arr = np.array(audio_seg.get_array_of_samples())
    if audio_seg.channels == 2:
        arr = arr.reshape((-1, 2))
        if merge_channels:
            arr = np.sum(arr, 1) / 2
            # arr = [0.5 * elem[0] + 0.5 * elem[1] for elem in arr]
    if normalized:
        return audio_seg.frame_rate, np.float32(arr) / 2**15
    else:
        return audio_seg.frame_rate, arr


def write_mp3(filename, arr, frame_rate, normalized=False):
    """numpy array to MP3"""
    channels = 2 if (arr.ndim == 2 and arr.shape[1] == 2) else 1
    if normalized:  # normalized array - each item should be a float in [-1, 1)
        y = np.int16(arr * 2 ** 15)
    else:
        y = np.int16(arr)
    song = pydub.AudioSegment(y.tobytes(), frame_rate=frame_rate, sample_width=2, channels=channels)
    song.export(filename, format="mp3", bitrate="196k")


def is_power_of_two(n):
    return (n != 0) and (n & (n-1) == 0)


def is_symmetrical(arr):
    return all([arr[idx] == arr[-idx - 1] for idx in range(0, int(len(arr) / 2))])
