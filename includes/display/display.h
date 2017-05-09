#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class display
{
    public:
        display(int width, int height, const std::string& title);


        void swapBuffers();
        void clear(float r, float g, float b, float a);

        virtual ~display();

    protected:
    private:

        SDL_Window* myWindow;
        SDL_GLContext myGlContext;

        bool myRUNNING;

};

#endif // DISPLAY_H
