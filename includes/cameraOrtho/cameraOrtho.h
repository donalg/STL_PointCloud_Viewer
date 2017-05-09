#ifndef CAMERAORTHO_H
#define CAMERAORTHO_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera
{
public:
  camera(const glm::vec3 pos, float width, float height, float zoom)
  {
    myWidth = width;
    myHeight = height;
    myZoom = zoom;
    myOrtho = glm::ortho(-(5*myWidth)/(2*myZoom),  (5*myWidth)/(2*myZoom), -(5*myHeight)/(2*myZoom), (5*myHeight)/(2*myZoom), 0.1f, 100000000000.0f);
    myPosition = pos;
    myForward = glm::vec3(0,0,1);
    myUp = glm::vec3(0,1,0);

  }

  inline glm::mat4 getViewProjection() const
  {
    return myOrtho * glm::lookAt(myPosition, glm::vec3(0,0,0), myUp);
  }

  inline void upDateZoom(float zoom)
  {
    myZoom = zoom;
    myOrtho = glm::ortho(-(5*myWidth)/(2*myZoom),  (5*myWidth)/(2*myZoom), -(5*myHeight)/(2*myZoom), (5*myHeight)/(2*myZoom), 0.1f, 100000000000.0f);
  }

  inline float getZoom()
  {
      return myZoom;
  }


protected:
private:
  glm::mat4 myOrtho;
  float zoom;
  glm::vec3 myPosition;
  glm::vec3 myForward;
  glm::vec3 myUp;
  float myWidth, myHeight, myZoom;

};

#endif // CAMERA_H
