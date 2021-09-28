import numpy as np
import time
from model import Model
from view import View
from controller import Controller
from utils import *


if __name__ == "__main__":
    #img = parse_GOL_file("patterns/knightship.txt", 'O')
    img = np.random.randint(low=0, high=2, size=(SIZE[0], SIZE[1]), dtype=np.uint8) * 255


    model = Model(SIZE[0], SIZE[1], img)
    view = View(model)

    controller = Controller(model, view)

    controller.run()

