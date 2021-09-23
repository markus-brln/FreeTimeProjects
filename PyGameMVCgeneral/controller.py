from model import Model
from view import View
from utils import *

import pygame as pg
import numpy as np

class Controller:
    def __init__(self, model=Model, view=View):
        self.model = model
        self.view = view

        self.running = True

        self.image = np.zeros(shape=(SIZE[1], SIZE[0], 3))
        for x in range(SIZE[0]):
            for y in range(SIZE[1]):
                self.image[y][x] = (x, y, 0)

    def run(self):
        pg.init()
        screen = pg.display.set_mode(SIZE)
        clock = pg.time.Clock()

        #colors = np.array([[120, 250, 90], [250, 90, 120], [255, 255, 255]])
        #picture = np.random.randint(3, size=(20, 20))
        #surface = pg.surfarray.make_surface(colors[picture])
        #surface = pg.surfarray.make_surface(self.image)
        #surface = pg.transform.scale(surface, SIZE)  # Scaled a bit.
        iter = 0
        while self.running:
            iter = iter + 1
            self.handle_events()
            self.handle_key_presses()
            screen.fill((0, 0, 0))
            #for x in range(SIZE[0]):
            #    for y in range(SIZE[1]):
            #        surface.set_at((x, y), (x, y, 0))

            self.view.construct_image(self.image, iter)
            surface = pg.surfarray.make_surface(self.image)
            screen.blit(surface, (0, 0))

            pg.display.flip()
            clock.tick(30)


    def handle_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False

    def handle_key_presses(self):
        keys = pg.key.get_pressed()
        if keys[pg.K_LEFT]:
            print("hi")
        if keys[pg.K_RIGHT]:
            print("hmm")



