#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../includes/display/display.h"
#include "../includes/shader/shader.h"
#include "../includes/mesh/mesh.h"
#include "../includes/texture/texture.h"
#include "../includes/transform/transform.h"
#include "../includes/camera/camera.h"
#include "../includes/model/model.h"

#define WIDTH 1000
#define HEIGHT 600

#define meshTRIANGLES  0 // Define parameters for the drawings:
#define meshLINES  1
#define meshPOINTS  2

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
		camera Camera(glm::vec3(0,0,-100), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
		transform Transform;

		modelFileName = "../resources/STLfiles/lfs_elephant.stl";
		model Model(modelFileName);

		mesh Mesh(Model);

		float counter = 0.0f;

		Transform.getPos().y = -1.5;
		Transform.getRot().z = -90.0f;
		Transform.getRot().x = -90.0f;
    while(Display.running())
    {
     	Display.clear(0.0f, 0.15f, 0.3f, 1.0f);

			Transform.getRot().y = counter * 1.5;
			Transform.getRot().x = counter * 1.5;
			Transform.getRot().z = counter * 1.5;

     	Shader.bind();
			Texture.bind(0);
			Shader.update(Transform, Camera);

     	Mesh.draw(meshLINES);

      Display.swapBuffers(&Transform);

			counter += 0.01f;

    }

    return 0;
}
