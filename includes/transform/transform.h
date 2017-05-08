#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class transform
{
public:
  transform(const glm::vec3 pos = glm::vec3(), const glm::vec3 rot = glm::vec3(), const glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
    myPos(pos),
    myRot(rot),
    myScale(scale) {}

    inline glm::mat4 getModel() const
    {
        glm::mat4 posMatrix = glm::translate(myPos);
        glm::mat4 rotXMatrix = glm::rotate(myRot.x, glm::vec3(1,0,0));
        glm::mat4 rotYMatrix = glm::rotate(myRot.y, glm::vec3(0,1,0));
        glm::mat4 rotZMatrix = glm::rotate(myRot.z, glm::vec3(0,0,1));
        glm::mat4 scaleMatrix = glm::translate(myScale);

        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        return posMatrix * rotMatrix * scaleMatrix; // Scale firts rotate next then translate
    }

  inline glm::vec3& getPos() {return myPos;}
  inline glm::vec3& getRot() {return myRot;}
  inline glm::vec3& getScale() {return myScale;}

  inline void setPos(glm::vec3& pos) {myPos = pos; }
  inline void setRot(glm::vec3& rot) {myRot = rot; }
  inline void setScale(glm::vec3& scale) {myScale = scale;}

protected:
private:
  glm::vec3 myPos;
  glm::vec3 myRot;
  glm::vec3 myScale;


};

#endif
