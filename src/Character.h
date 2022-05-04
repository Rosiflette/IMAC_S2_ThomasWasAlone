#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"

class Character : public Rectangle {
  private : // récupère les mêmes attributs et fonctions que dans Rectangle
    glm::vec2 positionArrivee;
    

  public:
    bool isJumping;
    Character();
    Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee);
    void displayValues();
    void move(float deltaTime);
    void jump(float velocity, float deltaTime);
    void gravity(float deltaTime);
    bool collision(Rectangle r);



};

#endif //CHARACTER_H
