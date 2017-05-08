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

#define WIDTH 800
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
		camera Camera(glm::vec3(0,0,-7), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
		transform Transform;

		modelFileName = "../resources/STLfiles/BinaryFiles/cube.stl";
		model Model(modelFileName);

		mesh Mesh(Model);

		for (unsigned int i = 0; i < Model.positions.size(); i++)
		{
			std::cout << "Position: " << i << std::endl;
			std::cout << "Values: \t";
			for (unsigned int j = 0; j < 3; j++)
			{
				std::cout << Model.positions[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		for (unsigned int i = 0; i < Model.indices.size(); i++)
		{
			std::cout << "Index Reference: " << i << std::endl;
			std::cout << "Values: \t";
			for (unsigned int j = 0; j < 3; j++)
			{
				std::cout << Model.positions[Model.indices[i]][j] << "\t";
			}
			std::cout << std::endl;
		}


		float counter = 0.0f;
		Transform.getPos().y = -1.5;
    while(Display.running())
    {
     	Display.clear(0.0f, 0.15f, 0.3f, 1.0f);

			Transform.getRot().y = counter * 1.5;

     	Shader.bind();
			Texture.bind(0);
			Shader.update(Transform, Camera);

     	Mesh.draw(meshLINES);

      Display.swapBuffers();

			counter += 0.01f;

    }

    return 0;
}
