#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "helpers/RootDir.hpp"

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
        void draw();

        // GETTER
        glm::vec2 getPosUpperLeft();
        glm::vec2 getPosUpperRight();
        glm::vec2 getPosBottomLeft();
        glm::vec2 getPosBottomRight();
        glm::vec3 getColor();

};

#endif // RECTANGLE_H
