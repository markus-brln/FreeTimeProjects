import numpy as np
from numba import cuda
from enum import Enum
import math
import pygame as pg

SIZE = (500, 500)
RECURSION_DEPTH = 1


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

def normalize_vec(x, y, z):
    length = math.sqrt(x * x + y * y + z * z)
    return x / length, y / length, z / length
# turn vector into length of 1

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
    vecCopy = vec
    # vec.x = same
    vec[1] = vecCopy[1] * math.cos(x_rot) - vecCopy[2] * math.sin(x_rot)
    vec[2] = vecCopy[1] * math.sin(x_rot) + vecCopy[2] * math.cos(x_rot)

    # roation around y
    #| cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    #|   0      1       0| |y| = |         y        | = |y'|
    #|−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|
    vecCopy = vec
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

def solve_quadratic(a, b, c):
    discr = b * b - 4.0 * a * c

    if discr < 0.0:
        return 0, 0, False

    if discr == 0.0:
        x0 = x1 = -0.5 * b / a
    else:
        q = 0
        if b > 0.0:
            q = -0.5 * (b + math.sqrt(discr))
        else:
            q = -0.5 * (b - math.sqrt(discr))
        x0 = q / a
        x1 = c / q

    if x0 > x1:
        h = x0
        x0 = x1
        x1 = h

    return x0, x1, True


def intersect_sphere(cam_pos, ray_dir, objects, idx_obj_arr):
    # Sphere formula: | | x - position | | ^ 2 = r ^ 2
    # Line formula: x = ray.O + t * ray.D
    # [SPHERE,   R, G, B, ka, kd, ks, n, texture_nr, radius, x, y, z]
    #print(ray_dir[0],ray_dir[1],ray_dir[2], objects[0])
    sphere_pos = objects[idx_obj_arr + 10], objects[idx_obj_arr + 11], objects[idx_obj_arr + 12]

    # Vector L = ray.O - position; [original C++ code]
    line_vec = (cam_pos[0] - sphere_pos[0], cam_pos[1] - sphere_pos[1], cam_pos[2] - sphere_pos[2])
    # double a = ray.D.dot(ray.D);
    a = ray_dir[0] * ray_dir[0] + ray_dir[1] * ray_dir[1] + ray_dir[2] * ray_dir[2]
    # double b = 2.0 * ray.D.dot(L);
    b = 2.0 * (ray_dir[0] * line_vec[0] + ray_dir[1] * line_vec[1] + ray_dir[2] * line_vec[2])
    #  double c = L.dot(L) - r * r;
    c = line_vec[0] * line_vec[0] + line_vec[1] * line_vec[1] + line_vec[2] * line_vec[2] - objects[idx_obj_arr + 9]

    t0, t1, solved_bool = gpu_solve_quadratic(a, b, c)
    normal_x, normal_y, normal_z, hit_bool = 0, 0, 0, False

    if not solved_bool:
        return t0, normal_x, normal_y, normal_z, hit_bool

    if t0 < 0.0:
        t0 = t1
        if t0 < 0.0:
            return t0, normal_x, normal_y, normal_z, hit_bool

    # calculate normal on hitpoint
    hit_point = cam_pos[0] + t0 * ray_dir[0], cam_pos[1] + t0 * ray_dir[1], cam_pos[2] + t0 * ray_dir[2]
    normal = hit_point[0] - sphere_pos[0], hit_point[1] - sphere_pos[1], hit_point[2] - sphere_pos[2]
    normal_x, normal_y, normal_z = gpu_normalize_vec(normal[0], normal[1], normal[2])
    hit_bool = True
    return t0, normal_x, normal_y, normal_z, hit_bool


def cast_ray(cam_pos, ray_dir, objects):
    n_objects = objects[0]
    idx_obj_arr = 1
    hit_dist = 10000000000              # get hit with closest distance
    hit_recorded = False                    # ray hit any object at all?
    hit_obj_idx = 1                         # idx in objects array at which object can be found,
                                            # important for coloring
    min_hit_normal = (1, 0, 0)              # normal of hitpoint at closest obj

    for idx in range(n_objects):
        if objects[idx_obj_arr] == 1:   # ObjectTypes.SPHERE.value
            t0, normal_x, normal_y, normal_z, hit_bool = gpu_intersect_sphere(cam_pos, ray_dir, objects, idx_obj_arr)
            if hit_bool:
                hit_recorded = True
                if t0 > hit_dist:
                    hit_dist = t0
                    hit_obj_idx = idx_obj_arr # object with closest hit
                    min_hit_normal = (normal_x, normal_y, normal_z)

            idx_obj_arr += 13       # step through obj data array manually

    norm_x, norm_y, norm_z = min_hit_normal
    return norm_x, norm_y, norm_z, hit_dist, hit_recorded, hit_obj_idx

def trace(cam_pos, ray_dir, lights, objects, rec_depth):

    norm_x, norm_y, norm_z, hit_dist, hit_recorded, hit_obj_idx = gpu_cast_ray(cam_pos, ray_dir, objects)

    if hit_recorded:
        return 255, 255, 255
    return 0, 0, 0




gpu_normalize_vec = cuda.jit(device=True)(normalize_vec)
gpu_distance2D = cuda.jit(device=True)(distance2D)
gpu_distance3D = cuda.jit(device=True)(distance3D)
gpu_angle = cuda.jit(device=True)(angle)
gpu_rotate_vector = cuda.jit(device=True)(rotate_vector)
gpu_solve_quadratic = cuda.jit(device=True)(solve_quadratic)
gpu_intersect_sphere = cuda.jit(device=True)(intersect_sphere)
gpu_cast_ray = cuda.jit(device=True)(cast_ray)
gpu_trace = cuda.jit(device=True)(trace)
