#include <iostream>
#include <GL/glew.h>
#include "important/source.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};


void draw()
{
    /*    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    */

    /*glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -1000.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 50, 1.f, 0.f, 0.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 30, 0.f, 1.f, 0.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 90, 0.f, 0.f, 1.f);

        glBegin(GL_QUADS);

        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f(50.f, 50.f, -50.f);
        glVertex3f(50.f, -50.f, -50.f);

        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f(50.f, 50.f, 50.f);
        glVertex3f(50.f, -50.f, 50.f);

        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f(-50.f, -50.f, 50.f);

        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f, 50.f, -50.f);
        glVertex3f(50.f, 50.f, 50.f);
        glVertex3f(50.f, -50.f, 50.f);

        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f, -50.f, 50.f);

        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f(50.f, 50.f, -50.f);
        glVertex3f(50.f, 50.f, 50.f);

        glEnd();*/
}

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

   
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

    // create the window
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...
    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.f, 1.f, -1.f, 1.f, 500.f, 2000.f);
    //gluPerspective(90.f, 1.f, 1.f, 500.f);

    sf::Clock clock;



    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        draw();
        
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}