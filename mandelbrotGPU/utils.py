from numba import cuda
import cmath

SIZE = (500, 500)
MAX_ITER = 200
N_COLOR_VAR = 3



def mandel(x, y, max_iters, mandel_power):
  """
    Given the real and imaginary parts of a complex number,
    determine if it is a candidate for membership in the Mandelbrot
    set given a fixed number of iterations.
  """
  if mandel_power < 0.05:
    mandel_power = 0.05

  c = complex(x, y)
  z = 0.0j
  for i in range(max_iters):
    #z = cmath.exp(x) + c
    #z = pow(z, mandel_power) + c
    z = z*z + c
    if (z.real*z.real + z.imag*z.imag) >= 4:
      return i

  return max_iters

mandel_gpu = cuda.jit(device=True)(mandel)