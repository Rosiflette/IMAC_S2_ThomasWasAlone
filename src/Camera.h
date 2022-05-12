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
    //glm::mat4 getProjection();
    void followCharacter(Character& car);

    //getters
    glm::vec2 getPosition();
    
};

#endif
