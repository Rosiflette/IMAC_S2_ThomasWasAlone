#include "Level.h"
#include <fstream>


Level::Level(){}


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
