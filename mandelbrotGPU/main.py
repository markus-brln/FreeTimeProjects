import numpy as np
import time
from model import Model
from view import View
from controller import Controller
from utils import *


if __name__ == "__main__":
    model = Model()
    view = View(model)

    controller = Controller(model, view)

    controller.run()