import numpy as np

SIZE = (600, 600)


def parse_GOL_file(file_path, on_sign):
    """Assumes that lines are of same length, or at least that the first line
    is of maximum length."""

    file = open(file_path, mode='r')
    lines = file.readlines()

    img = np.zeros(shape=(len(lines[0]), len(lines)))

    for y, line in enumerate(lines):
        for x, ch in enumerate(line):
            if ch == on_sign:
                img[x][y] = 1

    return img