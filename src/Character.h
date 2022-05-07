#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"
#include <vector>

class Character : public Rectangle {
  private : // récupère les mêmes attributs et fonctions que dans Rectangle
    glm::vec2 positionArrivee;
    float speed;
    

  public:
    bool isJumping;
    bool isMoving;
    Character();
    Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee);
    void displayValues();
    float calcMove(float velocity ,float deltaTime);
    void moveDown(float velocity, float deltaTime); //a enlever
    float jump(float velocity, float deltaTime);
    float gravity(float deltaTime);
    bool collision(Rectangle r, glm::vec2 dir);
    char whereIsCollision(Rectangle r, float mv);
    bool isCollision(std::vector<Rectangle> list, glm::vec2 dir);
   

    void setPositionX(float newPos);
    void setPositionY(float newPos);

    int setPositionIfCollision(Rectangle r, float mv, int direction);


};

#endif //CHARACTER_H
