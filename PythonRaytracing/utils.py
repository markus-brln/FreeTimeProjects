import numpy as np
from numba import cuda
from enum import Enum
import math

SIZE = (500, 500)

class ObjectTypes(Enum):
  """The values of the first element of array sent to the GPU, determine structure of array."""
  TRIANGLE = 0 # [TRIANGLE, R, G, B, ka, kd, ks, n, texture_nr, v00, v01, v02, v10, ...,  v22 (9 datapoints)]
  SPHERE = 1   # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
  QUAD = 2     # [QUAD,     R, G, B, ka, kd, ks, n, texture_nr, v00, ..., v32 (12 datapoints)]



def mandel(x, y, max_iters):
  """
    Given the real and imaginary parts of a complex number,
    determine if it is a candidate for membership in the Mandelbrot
    set given a fixed number of iterations.
  """
  c = complex(x, y)
  z = 0.0j
  for i in range(max_iters):
    z = z*z + c
    if (z.real*z.real + z.imag*z.imag) >= 4:
      return i

  return max_iters

gpu_mandel = cuda.jit(device=True)(mandel)

def distance2D(x1, y1, x2, y2):
    return math.sqrt(math.pow(x1 - x2, 2) + math.pow(y1 - y2, 2) )
# distance between 2 2D points

def distance3D(t1, t2):
    return math.sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2) + pow(t1.z - t2.z, 2))
# distance between 2 3D points


def angle(a, b):
    return math.acos(np.dot(a,b)/(np.sqrt(a.dot(a)) * np.sqrt(b.dot(b))))
# angle between 2 3D vectors


def rotate_vector(vec, x_rot, y_rot, z_rot):
    # ASCII way of writing the matrices & vectors down taken from:
    # https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

    # rotation around x
    #|1     0           0| |x|   |        x        |   |x'|
    #|0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    #|0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|
    vecCopy = np.copy(vec)
    # vec.x = same
    vec[1] = vecCopy[1] * math.cos(x_rot) - vecCopy[2] * math.sin(x_rot)
    vec[2] = vecCopy[1] * math.sin(x_rot) + vecCopy[2] * math.cos(x_rot)

    # roation around y
    #| cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    #|   0      1       0| |y| = |         y        | = |y'|
    #|−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|
    vecCopy = np.copy(vec)
    vec[0] = vecCopy[0] * math.cos(y_rot) + vecCopy[2] * math.sin(y_rot)
    # vec.y = same
    vec[2] = -vecCopy[0] * math.sin(y_rot) + vecCopy[2] * math.cos(y_rot)

    # rotation around z
    # |cos θ   −sin θ   0| |x|   |x cos θ − y sin θ|   |x'|
    # |sin θ    cos θ   0| |y| = |x sin θ + y cos θ| = |y'|
    # |  0       0      1| |z|   |        z        |   |z'|
    vecCopy = vec
    vec[0] = vecCopy[0] * math.cos(z_rot) - vecCopy[1] * math.sin(z_rot)
    vec[1] = vecCopy[0] * math.sin(z_rot) + vecCopy[1] * math.cos(z_rot)
    # vec.z = same
    return vec

gpu_distance2D = cuda.jit(device=True)(distance2D)
gpu_distance3D = cuda.jit(device=True)(distance3D)
gpu_angle = cuda.jit(device=True)(angle)
gpu_rotate_vector = cuda.jit(device=True)(rotate_vector)