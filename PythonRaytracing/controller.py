from model import Model
from view import View
from utils import *
import time
import pygame as pg
import numpy as np
import os

class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view
        pg.init()
        self.clock = pg.time.Clock()
        self.font = pg.font.SysFont("Arial", 10)
        self.running = True

    def update_screen_info(self):
        cam_position = int(self.view.cam_pos[0]), int(self.view.cam_pos[1]), int(self.view.cam_pos[2])
        info = str(int(self.clock.get_fps())) + \
               " cam_pos: " + str(cam_position) + \
               " zoom: " + str(round(self.view.zoom, 2))

        return self.font.render(info, True, pg.Color("coral"))


    def run(self):
        screen = pg.display.set_mode(SIZE, pg.RESIZABLE)

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
            screen.blit(self.update_screen_info(), (10, 0))
            pg.display.flip()
            #print("blit+flip: ", time.time() - start)
            self.clock.tick(20)


    def handle_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False

    def handle_key_presses(self):
        keys = pg.key.get_pressed()

        if keys[pg.K_BACKSPACE]:
            #self.view.camera_pos[0] = -0.0452407411
            #self.view.camera_pos[1] = 0.9868162204352258
            self.view.camera_pos[0] = 0.0
            self.view.camera_pos[1] = 0.0
            self.view.camera_pos[2] = 0.0
            self.view.zoom = 1

        if keys[pg.K_w]:
            self.view.translate_cam(0, 0, -20.0 / self.view.zoom)
        if keys[pg.K_s]:
            self.view.translate_cam(0, 0, 20.0 / self.view.zoom)
        if keys[pg.K_a]:
            self.view.translate_cam(-20.0 / self.view.zoom, 0, 0)
        if keys[pg.K_d]:
            self.view.translate_cam(20.0 / self.view.zoom, 0, 0)
        if keys[pg.K_q]:
            self.view.translate_cam(0, 20.0 / self.view.zoom, 0)
        if keys[pg.K_e]:
            self.view.translate_cam(0, -20.0 / self.view.zoom, 0)
        if keys[pg.K_KP_PLUS]:
            self.view.multiply_zoom(1.1)
        if keys[pg.K_KP_MINUS]:
            self.view.multiply_zoom(0.9)
        if keys[pg.K_UP]:
            self.view.rotate_cam(0.05, 0.0, 0.0)
        if keys[pg.K_DOWN]:
            self.view.rotate_cam(-0.05, 0.0, 0.0)
        if keys[pg.K_RIGHT]:
            self.view.rotate_cam(0.0, -0.05, 0.0)
        if keys[pg.K_LEFT]:
            self.view.rotate_cam(0.0, 0.05, 0.0)

        if keys[pg.K_ESCAPE]:
            self.running = False


