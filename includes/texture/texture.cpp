#include "texture.h"
#include "../stb_image/stb_image.h"
#include <cassert>
#include <iostream>

texture::texture(const std::string &filename)
{
  int width, height, numComponents;

  unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4); // read in an image from file name! byte data stored in data

  if(imageData == NULL)
  {
    std::cerr << "Texture Loading Failed" << std::endl;
  }

  glGenTextures(1, &myTexture); // Generate a texture object
  glBindTexture(GL_TEXTURE_2D, myTexture); // bind texture to a 2D image

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat pixel is exceed buffer
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear interpilate between pixels when minimising and maximising
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

  stbi_image_free(imageData);
}

void texture::bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, myTexture);
}

texture::~texture()
{
  glDeleteTextures(1, &myTexture);
}
