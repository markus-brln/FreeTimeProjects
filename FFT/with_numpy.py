import math

import cv2
import numpy as np
import matplotlib.pyplot as plt


def load_image(filename: str):
    img = cv2.imread(filename)  # reads an image in the BGR format
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)


def save_image(data: np.ndarray, filename: str = 'out_img', ext: str = 'jpeg'):
    cv2.imwrite(f'{filename}.{ext}', data)


def to_black_and_white(array: np.ndarray) -> np.ndarray:
    return np.round(np.mean(array, axis=2))


def plot_images(images: list[np.ndarray]):
    dims = [round(math.sqrt(len(images)))] * 2
    if dims[0] * dims[1] < len(images):
        dims[1] += 1
    f, axarr = plt.subplots(dims[0], dims[1])
    for idx, image in enumerate(images):
        axarr[math.floor(idx / dims[1])][math.floor(idx % dims[1])].imshow(image)
    plt.show()


def log_transform(image):
    c = 255 / np.log(1 + np.max(image))
    log_image = c * (np.log(image + 1))

    return np.array(log_image, dtype=np.uint8)


if __name__ == '__main__':
    data = load_image('assets/box.png')
    bw_img = to_black_and_white(data)
    save_image(bw_img, 'bw_img')

    bw_fft = np.fft.fft2(bw_img)
    bw_fft_real = np.round(np.real(bw_fft))
    bw_fft_imag = np.round(np.imag(bw_fft))
    bw_fft_real_log = log_transform(bw_fft_real)
    bw_fft_imag_log = log_transform(bw_fft_imag)
    # TODO try fftn and ifftn
    bw_i_fft = np.fft.ifft2(bw_fft)
    bw_i_fft_real = np.round(np.real(bw_i_fft))

    is_equal = np.all(np.equal(bw_img, bw_i_fft_real))

    plot_images([data, bw_img, bw_fft_real, bw_fft_imag_log, bw_fft_real_log, bw_i_fft_real])

    print()

