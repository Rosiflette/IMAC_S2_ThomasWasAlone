#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <glm/glm.hpp>
#include <iostream> 

class Rectangle{

    protected :
        // 2 vertex that define the Rectangle
        glm::vec2 topLeft;
        glm::vec2 botRight;
        float width;
        float height;
        glm::vec3 color;

    public :
        //constructors
        Rectangle();
        Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight);
        Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight, glm::vec3 col);
        void displayValues();
        void draw(int isFilled);

        // Si l'un des coins est dans le rectangle;
        bool isRectangleInRectangle(Rectangle r);

        // Return true si le point en paramètre est contenu dans le rectangle
        bool isPointInRectangle(glm::vec2 p);

        // GETTER
        glm::vec2 getPosUpperLeft();
        glm::vec2 getPosUpperRight();
        glm::vec2 getPosBottomLeft();
        glm::vec2 getPosBottomRight();
        glm::vec3 getColor();
        float getWidth();
        float getHeight();

        //moving platform
        void movingPlatform(float posX);

};

#endif // RECTANGLE_H
