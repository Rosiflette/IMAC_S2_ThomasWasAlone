#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"

class Character : public Rectangle {
  private : // récupère les mêmes attributs et fonctions que dans Rectangle
    glm::vec2 positionArrivee;

  public:
    Character() {}
};

#endif //CHARACTER_H
