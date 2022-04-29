#include "Level.h"
#include <fstream>


Level::Level(){}


// GETTER

Character Level::getCharacter(){
  return character;
}
std::vector<Rectangle> Level::getObstacles(){
  return obstacles;
}
