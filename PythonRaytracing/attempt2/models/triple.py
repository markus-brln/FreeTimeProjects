import numpy as np


class Triple(np.ndarray):

    def __new__(cls, a):
        if not len(a) == 3:
            raise ValueError('Triple constructed with wrong length!')

        obj = np.asarray(a[0:3]).view(cls)
        return obj


