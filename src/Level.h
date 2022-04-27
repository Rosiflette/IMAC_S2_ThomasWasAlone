#ifndef LEVEL_H
#define LEVEL_H
#include "Rectangle.h"
#include <iostream>
#include <string>


class Level{

    private :
      Rectangle* obstacles;
      int obstaclesLength;
      Rectangle character;

    public :
      Level();
      void split(std::string line, char delimiter, float arr[]);

      // GETTER
      Rectangle getCharacter();
      Rectangle* getObstacles();
      int getObstaclesLength();

};


#endif // LEVEL_H
