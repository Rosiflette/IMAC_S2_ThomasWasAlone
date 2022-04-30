#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <glm/glm.hpp>


#include <iostream> // for displayValues() function

class Rectangle{

    protected :
        //position refers to the upper left corner
        glm::vec2 position;
        float w;
        float h;
        glm::vec3 color;

    public :
        Rectangle();
        Rectangle(glm::vec2 position,float w,float h, glm::vec3 col);
        void displayValues();
        //void draw();

        // GETTER
        glm::vec2 getPosUpperLeft();
        glm::vec2 getPosUpperRight();
        glm::vec2 getPosBottomLeft();
        glm::vec2 getPosBottomRight();
        glm::vec3 getColor();

};

#endif // RECTANGLE_H
