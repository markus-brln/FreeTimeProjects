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
        self.progress_time = True
        self.max_fps = 300
        self.full_screen = False
        self.image = np.zeros(shape=(SIZE[0], SIZE[1]))

        pg.init()
        self.clock = pg.time.Clock()
        self.font = pg.font.SysFont("Arial", 10)
        #self.image_upscaled = np.zeros(shape=(SIZE[0] * 2, SIZE[1] * 2))


    def update_screen_info(self):
        info = "fps: " + str(int(self.clock.get_fps())) + \
               " fps goal: " + str(self.max_fps)

        return self.font.render(info, True, pg.Color("coral"))

    def run(self):
        if FULL_SCREEN:                     # change in utils.py
            screen = pg.display.set_mode((SIZE[0], SIZE[1]), flags=pg.FULLSCREEN)
        else:
            screen = pg.display.set_mode((SIZE[0], SIZE[1]))

        world1_active = True                # flips so that the next time step can be constructed from the previous one
        while self.running:
            self.handle_events()
            self.handle_key_presses()
            screen.fill((0, 0, 0))

            if self.progress_time:
                world1_active = not world1_active

            self.image = self.view.construct_image(world1_active, self.progress_time)

            surface = pg.surfarray.make_surface(self.image)
            screen.blit(surface, (0, 0))
            screen.blit(self.update_screen_info(), (int(SIZE[0] / 2), 0))
            pg.display.flip()
            self.clock.tick(self.max_fps)


    def handle_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
            if event.type == pg.KEYDOWN:
                if event.key == pg.K_KP_PLUS:
                    self.max_fps += 10
                if event.key == pg.K_KP_MINUS:
                    self.max_fps -= 10
                if event.key == pg.K_BACKSPACE:
                    self.model.reset_to_init_world()
                if event.key == pg.K_r:
                    self.model.reset_to_random_world()
                if event.key == pg.K_SPACE:
                    self.progress_time = not self.progress_time
                if event.key == pg.K_f:
                    self.full_screen = not self.full_screen
                if event.key == pg.K_ESCAPE:
                    self.running = False



    def handle_key_presses(self):
        keys = pg.key.get_pressed()





