#ifndef QUADTREE_H
#define QUADTREE_H
#include "Rectangle.h"
#include <glm/glm.hpp>
#include <vector>

//#define SIZE_QUADTREE 10;
const int SIZE_QUADTREE = 100;

class Quadtree{

    private :
        Rectangle section;
        std::vector<Rectangle> listRectangle;

        Quadtree* sectNO; // Section en haute à gauche
        Quadtree* sectNE; // Section en haut à droite
        Quadtree* sectSO; // Section en bas à gauche
        Quadtree* sectSE; // Section en bas à droite

    public :
        Quadtree();
        Quadtree(glm::vec2 tl, glm::vec2 br);

        // 1 si rectangle ajouté et 0 si rectangle pas ajouté
        int addRectangleIntoSection(Rectangle r, int currentHigh);

        void drawSection();
        bool isLeaf();
        std::vector<Rectangle> search(glm::vec2 position);
        std::vector<Rectangle> listRSection(glm::vec2 topLeft, glm::vec2 botRight);
        std::vector<Rectangle> seachListRectangles(glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 botLeft, glm::vec2 botRight);
        std::vector<Rectangle> addIfNotExist(std::vector<Rectangle> list, std::vector<Rectangle> toAdd);



};

#endif // QUADTREE_H
