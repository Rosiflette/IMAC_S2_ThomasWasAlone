#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>

#include "Character.h"


class Camera{
    private: 
    glm::vec2 position;
    float zoom;

    public:

    Camera();
    void followCharacter(Character& car);


    //getters
    glm::vec2 getPosition();
    glm::vec2 getTopLeft();
    glm::vec2 getTopRight();
    glm::vec2 getBottomLeft();
    glm::vec2 getBottomRight();

    //setter
    void setPosition(glm::vec2 pos);
};

#endif
