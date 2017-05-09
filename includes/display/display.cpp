#include "display.h"
#include <GL/glew.h>
#include <iostream>

display::display(int width, int height, const std::string& title)
{
    // constructor
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE; // Set windowing flags

    myWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    myGlContext = SDL_GL_CreateContext(myWindow);

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        std::cout << "Error String: " << glewGetErrorString(status) << std::endl;
        std::cerr << "Glew failed to initalise..." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);

    myRUNNING = true;

}

display::~display()
{
    // destructor
    SDL_GL_DeleteContext(myGlContext);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
}

void display::clear(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void display::swapBuffers() // Swap view buffers
{
    SDL_GL_SwapWindow(myWindow);
}
