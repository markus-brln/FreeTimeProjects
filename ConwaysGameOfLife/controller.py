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
        self.image = np.zeros(shape=(SIZE[0], SIZE[1]))

        pg.init()
        self.clock = pg.time.Clock()
        self.font = pg.font.SysFont("Arial", 10)
        #self.image_upscaled = np.zeros(shape=(SIZE[0] * 2, SIZE[1] * 2))

    def update_screen_info(self):
        info = str(int(self.clock.get_fps()))

        return self.font.render(info, True, pg.Color("coral"))

    def run(self):
        screen = pg.display.set_mode((SIZE[0], SIZE[1]))
        world1_active = True                # flip

        while self.running:
            self.handle_events()
            self.handle_key_presses()
            screen.fill((0, 0, 0))

            self.image = self.view.construct_image(world1_active)
            self.image = 255 * self.image
            #for x in range(SIZE[0]):
            #    for y in range(SIZE[1]):
            #        self.image_upscaled[x*2:x*2+1][y*2:y*2+1] = self.image[x][y]

            world1_active = not world1_active
            surface = pg.surfarray.make_surface(self.image)
            screen.blit(surface, (0, 0))
            screen.blit(self.update_screen_info(), (SIZE[0] - 20, 0))
            pg.display.flip()
            self.clock.tick()


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



