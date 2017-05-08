#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class texture
{

public:
   texture(const std::string &filename);

   void bind(unsigned int unit);

   virtual ~texture();

protected:
private:

  GLuint myTexture;

};

#endif // TEXTURE_H
