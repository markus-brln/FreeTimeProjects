from model import Model
from view import View
from utils import *
import time
import pygame as pg
import numpy as np
import os

class Controller:
    def __init__(self, model=Model, view=View):
        self.model = model
        self.view = view

        self.running = True



    def run(self):
        pg.init()

        screen = pg.display.set_mode(SIZE, pg.RESIZABLE)
        clock = pg.time.Clock()

        while self.running:
            start = time.time()
            self.handle_events()
            self.handle_key_presses()

            #print("handling events: ", time.time() - start)
            #screen.fill((0, 0, 0))
            #for x in range(SIZE[0]):
            #    for y in range(SIZE[1]):
            #        surface.set_at((x, y), (x, y, 0))

            #self.image = self.view.construct_image(self.image)
            surface = pg.surfarray.make_surface(self.view.construct_image())
            #print("make surface: ", time.time() - start)
            screen.blit(surface, (0, 0))

            pg.display.flip()
            #print("blit+flip: ", time.time() - start)
            #clock.tick(60)


    def handle_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False

    def handle_key_presses(self):
        keys = pg.key.get_pressed()

        if keys[pg.K_BACKSPACE]:
            #self.view.camera_pos[0] = -0.0452407411
            #self.view.camera_pos[1] = 0.9868162204352258
            self.view.camera_pos[0] = 0.001643721971153
            self.view.camera_pos[1] = 0.822467633298876
            self.view.zoom = 1

        if keys[pg.K_UP]:
            self.view.camera_pos[1] -= 0.1 / self.view.zoom
        if keys[pg.K_DOWN]:
            self.view.camera_pos[1] += 0.1 /  self.view.zoom
        if keys[pg.K_RIGHT]:
            self.view.camera_pos[0] += 0.1 / self.view.zoom
        if keys[pg.K_LEFT]:
            self.view.camera_pos[0] -= 0.1 / self.view.zoom
        if keys[pg.K_q]:
            self.view.zoom = self.view.zoom * 1.1
        if keys[pg.K_e]:
            self.view.zoom = self.view.zoom / 1.1
        if keys[pg.K_PLUS] or keys[pg.K_KP_PLUS]:
            self.view.coloring_var += 1
        if keys[pg.K_MINUS] or keys[pg.K_KP_MINUS]:
            self.view.coloring_var -= 1
        if keys[pg.K_ESCAPE]:
            self.running = False


