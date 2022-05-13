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
      std::vector<Character> characters;

    public :
      Level();

      // GETTER
      Character& getCharacter();
      std::vector<Character>& getCharacters();
      std::vector<Rectangle> getObstacles();

      // SETTER
      void setCharacter(Character c){
        this->character = c;
      }
      void addCharacters(Character c){
        this->characters.push_back(c);
      }
      void addObsacles(Rectangle r){
        this->obstacles.push_back(r);
      }

      void moveBack();

};


#endif // LEVEL_H
