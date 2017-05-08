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

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
		std::string current_exec_name = argv[0]; // Name of the current exec program
  	std::string shaderLocation;
		std::string textureLocation;
		std::string modelFileName;

  	shaderLocation = "../resources/shaders/basicShader";
		textureLocation = "../resources/textureImages/bricks.jpg";


		vertex vertices[] = { vertex( glm::vec3( -0.5 , -0.5 , 0.0 ), glm::vec2( 0.0 , 0.0 ) ),
						    					vertex( glm::vec3(  0.0 ,  0.5 , 0.0 ), glm::vec2( 0.5 , 1.0 ) ),
    					   	 			  vertex( glm::vec3(  0.5 , -0.5 , 0.0 ), glm::vec2( 1.0 , 0.0 ) )
    					 					 };

		unsigned int indicies[] = { 0, 1, 2 };

		std::cout << shaderLocation << std::endl;
		std::cout << textureLocation << std::endl;

    display Display(WIDTH,HEIGHT, "OpenGL Drawing");


  //  mesh Mesh(vertices, (sizeof(vertices)/sizeof(vertices[0])), indicies,  (sizeof(indicies)/sizeof(indicies[0])));
/*
		if (argc >1)
		{
		modelFileName = argv[1];
		std::cout << "File Name: " << modelFileName << std::endl;
		mesh Mesh(modelFileName);
	 	}
	 	else {
		mesh Mesh(vertices, (sizeof(vertices)/sizeof(vertices[0])), indicies,  (sizeof(indicies)/sizeof(indicies[0])));
		}
*/
    shader Shader(shaderLocation);
		texture Texture(textureLocation);
		camera Camera(glm::vec3(0,0,-7), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
		transform Transform;

		modelFileName = "../resources/OBJfiles/monkey3.obj";
		mesh Mesh(modelFileName);

		float counter = 0.0f;
		Transform.getPos().y = -1.5;
    while(Display.running())
    {
     	Display.clear(0.0f, 0.15f, 0.3f, 1.0f);

			//float sinCounter = sinf(counter);
			float cosCounter = cosf(counter);

			//Transform.getPos().x = sinCounter;
			//Transform.getRot().z = counter * 1.5;
			Transform.getRot().y = counter * 1.5;
			//Transform.getRot().x = counter * 1.5;
		///	Transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

     	Shader.bind();
			Texture.bind(0);
			Shader.update(Transform, Camera);
     	Mesh.draw();
      Display.swapBuffers();

			counter += 0.01f;
			//std::cout << "Transform: " << Transform.getPos().x  << "\t Transform: " << Transform.getPos().y << std::endl;

    }

    return 0;
}
