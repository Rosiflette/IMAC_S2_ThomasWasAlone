#ifndef LEVEL_H
#define LEVEL_H
#include "Rectangle.h"
#include "Character.h"
#include <iostream>
#include <string>
#include <vector>


class Level{

    private :
      std::vector<Rectangle> obstacles;
      Character character;

    public :
      Level();
      void split(std::string line, char delimiter, float arr[]);

      // GETTER
      Character getCharacter();
      std::vector<Rectangle> getObstacles();

};


#endif // LEVEL_H
