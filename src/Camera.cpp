
#include "Camera.h"
#include "glad/glad.h"
#include <stdlib.h>

//CONSTRUCTOR
Camera::Camera(){
    this->position = glm::vec2(0,0);
    this->zoom = 1;
}


void Camera::followCharacter(Character& car){

        glMatrixMode(GL_MODELVIEW);
        float distancePersoHori = this->position.x - (car.getPosUpperLeft().x + car.getWidth()/2);
        float distancePersoVert = this->position.y - (car.getPosUpperLeft().y + car.getHeight()/2);

        glTranslatef(distancePersoHori,0,0);

        this->position.x = car.getPosUpperLeft().x + car.getWidth()/2;
        this->position.y = car.getPosUpperLeft().y + car.getHeight()/2;


}

glm::vec2 Camera::getPosition(){
    
    return glm::vec2(this->position.x, this->position.y);
}

