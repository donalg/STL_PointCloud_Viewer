#include <iostream>
#include <string>
#include <thread>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../includes/display/display.h"
#include "../includes/shader/shader.h"
#include "../includes/mesh/mesh.h"
#include "../includes/texture/texture.h"
#include "../includes/transform/transform.h"
#include "../includes/cameraOrtho/cameraOrtho.h"
#include "../includes/model/model.h"

#define WIDTH 1000
#define HEIGHT 800

#define meshTRIANGLES  0 // Define parameters for the drawings:
#define meshLINES  1
#define meshPOINTS  2

bool displayUpdater(transform& Transform, camera &Cam);

int main(int argc, char* argv[])
{
		std::string current_exec_name = argv[0]; // Name of the current exec program
  	std::string shaderLocation;
		std::string textureLocation;
		std::string modelFileName;

  	shaderLocation = "../resources/shaders/colorShader"; // Get ready to write more of these:
		textureLocation = "../resources/textureImages/bricks.jpg"; // This wont be used for the STL viewer (honeslty useless)

		std::cout << shaderLocation << std::endl;
		std::cout << textureLocation << std::endl;



    display Display(WIDTH,HEIGHT, "OpenGL Drawing");

    shader Shader(shaderLocation);
		texture Texture(textureLocation);
		// Perspective: camera Camera(glm::vec3(0,0,-100), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
 		camera Camera(glm::vec3(0,0,-10), (float)WIDTH, (float)HEIGHT, 10.0f); // Orthographic

		modelFileName = "../resources/STLfiles/lfs_elephant.stl";
		model Model(modelFileName);

		mesh Mesh(Model);

		transform Transform;
		Transform.getPos().y = -10;
		Transform.getRot().z = -90.0f;
		Transform.getRot().x = -90.0f;

		// Do window stuff here:
		bool isRunning = true;

    while(isRunning)
    {
     	Display.clear(0.0f, 0.15f, 0.25f, 0.8f);

			isRunning = displayUpdater(Transform, Camera);

     	Shader.bind();
			Texture.bind(0);
			Shader.update(Transform, Camera);

     	Mesh.draw(meshPOINTS);

      Display.swapBuffers();

    }

    return 0;
}

/////////////////////////////////////////////// Used to updat the transform matrix to alter view:
bool displayUpdater(transform &TransformMAT, camera &Cam) // Fis weird zoom ezpanding effects!
{
  bool mouseMotion = false; unsigned int mouseMotionIndex = 0;
	bool zoom = false, translate = false, rotate = false;
	float zoomFloat = Cam.getZoom();
	bool RUNNING = true;
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
          RUNNING = false;
					break;
      case SDL_MOUSEMOTION:
						mouseMotion = true;
						mouseMotionIndex = i;
			case SDL_KEYDOWN:
						switch (events[i].key.keysym.sym)
						 {
							case SDLK_t:
									translate = true;
									break;
							case SDLK_r:
									rotate = true;
									break;
							case SDLK_z:
									zoom = true;
									break;
						}
    }
  }
	if (mouseMotion)
	{
			if(translate)
			{
				TransformMAT.getPos().x += -1.5*events[mouseMotionIndex].motion.xrel;
		    TransformMAT.getPos().y += -1.5*events[mouseMotionIndex].motion.yrel;
			}
			if(zoom)
			{
				zoomFloat += events[mouseMotionIndex].motion.yrel;
				if (zoomFloat < 0.5) {zoomFloat = 0.5; }
				Cam.upDateZoom(zoomFloat);
			}
			if (rotate)
			{
				TransformMAT.getRot().x += 0.2*events[mouseMotionIndex].motion.xrel;
				TransformMAT.getRot().y += 0.2*events[mouseMotionIndex].motion.yrel;
			}
	}
	// Clear events Buffer:
	events.clear();
	return RUNNING;
}

/////////////////////////////////////////////// Create GUI here:
