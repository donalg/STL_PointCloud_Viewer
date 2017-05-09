#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "../transform/transform.h"
#include "../cameraOrtho/cameraOrtho.h"

class shader
{
public:
	shader(const std::string& fileName);

	void bind();
	void update(const transform& Transform, const camera& Camera);

	virtual ~shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};


	GLuint myProgram;
	GLuint myShaders[NUM_SHADERS];
	GLuint myUniforms[NUM_UNIFORMS];
};

#endif
