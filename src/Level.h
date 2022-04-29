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

      // GETTER
      Character getCharacter();
      std::vector<Rectangle> getObstacles();

      // SETTER
      void setCharacter(Character c){
        this->character = c;
      }
      void addObsacles(Rectangle r){
        this->obstacles.push_back(r);
      }

};


#endif // LEVEL_H
