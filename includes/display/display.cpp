#include "display.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>

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

    myWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

void display::swapBuffers(transform *Transform)
{
    SDL_GL_SwapWindow(myWindow);

    bool keyDown = false; unsigned int kdownEI = 0;
    bool mouseMove = false; unsigned int MmoveEI = 0;

    std::vector <SDL_Event> events;
    SDL_Event e;
    // Pole and store events:
    while (SDL_PollEvent(&e) != 0)
    {
      events.push_back(e);
    }

    // Read events and set flags:
    for (unsigned int i = 0; i < events.size(); i++)
    {
      switch (events[i].type)
      {
        case SDL_QUIT:
            myRUNNING = false;
        case SDL_MOUSEMOTION:
            mouseMove = true;
            MmoveEI = i;
        case SDL_KEYDOWN:
            keyDown = true;
            kdownEI = i;
      }
    }

    // Check flags and make changes:
  if ((keyDown) && (mouseMove)) // && (e.type == SDL_MOUSEBUTTONDOWN))
  {
    if (events[kdownEI].key.keysym.sym == SDLK_t) // Translate
    {
      Transform->getPos().x += -events[MmoveEI].motion.xrel;
      Transform->getPos().y += -events[MmoveEI].motion.yrel;
    }
    else if (events[kdownEI].key.keysym.sym == SDLK_r) // Rotate;
    {
      // Do this later
    }
  }

  // Clear events Buffer:
  events.clear();

}

bool display::running()
{
    return myRUNNING;
}
