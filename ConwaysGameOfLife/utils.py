import numpy as np

def get_screen_size():
    import ctypes
    user32 = ctypes.windll.user32
    return user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)

# change to True, SIZE = get_screen_size() if full screen is desired
FULL_SCREEN = False
SIZE = (500, 500) #get_screen_size()





def parse_GOL_file(file_path, on_sign):
    """Assumes that lines are of same length, or at least that the first line
    is of maximum length."""

    file = open(file_path, mode='r')
    lines = file.readlines()

    img = np.zeros(shape=(len(lines[0]), len(lines)))

    for y, line in enumerate(lines):
        for x, ch in enumerate(line):
            if ch == on_sign:
                img[x][y] = 255

    return img