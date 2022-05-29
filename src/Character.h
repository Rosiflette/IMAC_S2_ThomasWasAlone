#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"
#include <vector>


class Character : public Rectangle {
  private : //Is a rectangle child
    glm::vec2 positionArrivee;
    float jumpPower;




  public:
    Character();
    Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee,float jumpPower);

    glm::vec2 velocity;
    float acceleration;

    //Getter
    glm::vec2 getPosFinal();
    float getJumpPower();

    //Setter
    void setPositionX(float newPos);
    void setPositionY(float newPos);

    //Collision and movements
    bool collision(Rectangle r, glm::vec2 dir);
    bool inCollision(std::vector<Rectangle> listR,glm::vec2 dir);
    glm::vec2 getValMouvments(glm::vec2 acc);
    void mouvments(glm::vec2 acc, float deltaTime);
    float collisionHorizontal(Rectangle r, glm::vec2 nextMove);
    float collisionVertical(Rectangle r, glm::vec2 nextMove);
    void setFinalPos();

    
    void drawFinalPos();
    bool isInFinalPos();
    void displayValues();

};

#endif //CHARACTER_H
