#include "Level.h"
#include "Constants.h"

#include <fstream>


Level::Level(){
  this->obstaclesLength = 0;
  char delimiter = ';';
  std::string line;
  std::ifstream myfile ("src/levels.txt");
  if (myfile.is_open())
  {
    getline(myfile, line);
    if(!line.compare("MAPS")){
      getline(myfile,line);
      while (line.compare("/")){
        int length = 7;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Rectangle r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]));
        this->obstacles[obstaclesLength] = r;
        this->obstaclesLength++;
        delete [] valueArray;
        getline(myfile,line);
      }
    }
    getline(myfile,line);
    if(!line.compare("CHARACTER")){
      getline(myfile,line);
      while (line.compare("/")){
        int length = 7;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Rectangle r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]));
        this->character = r;
        delete [] valueArray;
        getline(myfile,line);
      }
    }
    myfile.close();
  }
  else{
    std::cout << "error !!" << std::endl;
  }
}

void Level::split(std::string line, char delimiter, float arr[]){
  std::string val;
  size_t pos = 0;
  int size = 0;
  while ((pos = line.find(delimiter)) != std::string::npos) { // npos => quand il n'y a pas eu de delimmiter trouvé
      val = line.substr(0, pos);
      arr[size] = std::stof(val);
      size++;
      line.erase(0, pos + 1);
  }
}



// GETTER

Rectangle Level::getCharacter(){
  return character;
}
Rectangle* Level::getObstacles(){
  return obstacles;
}
int Level::getObstaclesLength(){
  return obstaclesLength;
}
