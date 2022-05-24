#include "Level.h"
#include <fstream>


Level::Level(){
  this->numLvl = 0;
}


// GETTER

Character& Level::getCharacter(){
  return character;
}

std::vector<Character>& Level::getCharacters(){
  return characters;
}

std::vector<Rectangle> Level::getObstacles(){
  return obstacles;
}

std::vector<glm::vec2>& Level::getScreenLvl(){
  return posScreen;
}

