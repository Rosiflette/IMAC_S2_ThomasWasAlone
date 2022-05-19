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
      glm::vec2 posBottomRightLvl;

    public :
      Level();

      // GETTER
      Character& getCharacter();
      std::vector<Character>& getCharacters();
      std::vector<Rectangle> getObstacles();
      glm::vec2& getPosBottomRightLvl();

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
      void setPosBottomRightLvl(glm::vec2 posBR){
        this->posBottomRightLvl = posBR;
      }

      void moveBack();

};


#endif // LEVEL_H
