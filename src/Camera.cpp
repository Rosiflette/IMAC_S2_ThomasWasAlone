
#include "Camera.h"
#include "glad/glad.h"
#include <stdlib.h>

//CONSTRUCTOR
Camera::Camera(){
    this->position = glm::vec3(0,0,3);
    this->zoom = 1;
}

//GET THE POSITION AND ZOOM OF THE CAMERA
// glm::mat4 Camera::getProjection(){

//     //calculate the borders of the camera
//     float left = this->position.x - app.getWidth();
//     float right = this->position.x + app.getWidth();
//     float top = this->position.y - app.getHeight();
//     float bot = this->position.y + app.getHeight();


//     //create the orthogonal maxtrix;

//     glm::mat4 orthoMatrix = glm::mat4(left,right,bot,top);
//     glm::mat4 scaleMatrix = glm::scale(this->zoom);

//     return orthoMatrix * scaleMatrix;
// }

void Camera::followCharacter(Character& car){

        glMatrixMode(GL_MODELVIEW);
        float distancePersoHori = this->position.x - (car.getPosUpperLeft().x + car.getWidth()/2);
        float distancePersoVert = this->position.y - (car.getPosUpperLeft().y + car.getHeight()/2);

        glTranslatef(distancePersoHori,distancePersoVert,0);

        this->position.x = car.getPosUpperLeft().x + car.getWidth()/2;
        this->position.y = car.getPosUpperLeft().y + car.getHeight()/2;


}

glm::vec2 Camera::getPosition(){
    
    return glm::vec2(this->position.x, this->position.y);
}