import math
import random


def basic_array(pow_two=8):
    length = int((2 ** pow_two) / 2)
    return [0.0] * length + [1.0] * length


def random_array(pow_two=8, value_range=None):
    if value_range is None:
        value_range = [0, 255]
    return [random.randint(value_range[0], value_range[1]) for _ in range(2 ** pow_two)]


def cos_array(pow_two=8, max_val=255, iterations=10):
    length = 2 ** pow_two
    return [math.floor(((math.cos((idx * math.pi) / (length / iterations)) + 1) / 2) * max_val) for idx in range(length)]
