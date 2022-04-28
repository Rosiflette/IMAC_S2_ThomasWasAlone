#ifndef LEVEL_H
#define LEVEL_H
#include "Rectangle.h"
#include <iostream>
#include <string>
#include <vector>


class Level{

    private :
      std::vector<Rectangle> obstacles;
      Rectangle character;

    public :
      Level();
      void split(std::string line, char delimiter, float arr[]);

      // GETTER
      Rectangle getCharacter();
      std::vector<Rectangle> getObstacles();

};


#endif // LEVEL_H
