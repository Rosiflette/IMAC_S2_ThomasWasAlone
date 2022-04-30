#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"

class Character : public Rectangle {
  private : // récupère les mêmes attributs et fonctions que dans Rectangle
    glm::vec2 positionArrivee;

  public:
    Character();
    Character(glm::vec2 pos,float w,float h, glm::vec3 col, glm::vec2 positionArrivee);
    void displayValues();
    void move(float deltaTime);
    void jump(float deltaTime);
};

#endif //CHARACTER_H
