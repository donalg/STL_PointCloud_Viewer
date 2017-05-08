#include "shader.h"
#include <iostream>
#include <fstream>

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);
static GLuint createShader(const std::string& text, unsigned int type);

shader::shader(const std::string& fileName)
{
	myProgram = glCreateProgram();
	myShaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	myShaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
  {
		glAttachShader(myProgram, myShaders[i]);
  }

	glBindAttribLocation(myProgram, 0, "position");
	glBindAttribLocation(myProgram, 1, "texCoord");
	glBindAttribLocation(myProgram, 2, "normal");

	glLinkProgram(myProgram);
	checkShaderError(myProgram, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(myProgram);
	checkShaderError(myProgram, GL_LINK_STATUS, true, "Error: Program is invalid: ");

	myUniforms[TRANSFORM_U] = glGetUniformLocation(myProgram, "Transform");

}

shader::~shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(myProgram, myShaders[i]);
        glDeleteShader(myShaders[i]);
    }

	glDeleteProgram(myProgram);
}

void shader::bind()
{
	glUseProgram(myProgram);
}

void shader::update(const transform& Transform, const camera& Camera)
{
		glm::mat4 model =  Camera.getViewProjection() * Transform.getModel();
		glUniformMatrix4fv(myUniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static std::string loadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
						output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

static GLuint createShader(const std::string& text, unsigned int type)
{
    GLuint newShader = glCreateShader(type);

    if(newShader == 0)
    {
				std::cerr << "Error compiling shader type " << type << std::endl;
    }

    const GLchar* shaderSourceStrings[1];
		GLint shaderSourceStringsLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLengths[0] = text.length();

    glShaderSource(newShader, 1, shaderSourceStrings, shaderSourceStringsLengths);
    glCompileShader(newShader);

    checkShaderError(newShader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return newShader;
}
