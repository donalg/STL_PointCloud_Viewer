#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera
{
public:
  camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
  {
    myPerspective = glm::perspective(fov, aspect, zNear, zFar);
    myPosition = pos;
    myForward = glm::vec3(0,0,1);
    myUp = glm::vec3(0,1,0);
  }

  inline glm::mat4 getViewProjection() const
  {
    return myPerspective * glm::lookAt(myPosition, myPosition + myForward, myUp);
  }

protected:
private:
  glm::mat4 myPerspective;
  glm::vec3 myPosition;
  glm::vec3 myForward;
  glm::vec3 myUp;

};

#endif // CAMERA_H
