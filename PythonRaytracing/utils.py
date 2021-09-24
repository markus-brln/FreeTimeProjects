from numba import cuda
from enum import Enum

SIZE = (500, 500)
MAX_ITER = 1500
N_COLOR_VAR = 3

class ObjectTypes(Enum):
  """The values of the first element of array sent to the GPU, determine structure of array."""
  LIGHT = 0    # [LIGHT,    R, G, B, x, y, z]
  TRIANGLE = 1 # [TRIANGLE, R, G, B, ka, kd, ks, n, texture_nr, v00, v01, v02, v10, ...,  v22 (9 datapoints)]
  SPHERE = 2   # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
  QUAD = 3     # [QUAD,     R, G, B, ka, kd, ks, n, texture_nr, v00, ..., v32 (12 datapoints)]



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

mandel_gpu = cuda.jit(device=True)(mandel)