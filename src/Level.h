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
      std::vector<glm::vec2> posScreen;
      int numLvl;

    public :
      Level();

      // GETTER
      Character& getCharacter();
      std::vector<Character>& getCharacters();
      std::vector<Rectangle> getObstacles();
      glm::vec2& getPosBottomRightLvl();
      std::vector<glm::vec2>& getScreenLvl();

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
      void setScreenLvl(std::vector<glm::vec2> s){
        this->posScreen = s;
      }

      void setNumLevel(int n){
        this->numLvl = n;
      }

      int getNumLevel(){
        return numLvl;
      }

      void moveBack();

};


#endif // LEVEL_H
