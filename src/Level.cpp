#include "Level.h"
#include "Constants.h"

#include <fstream>


Level::Level(){

  char delimiter = ';';
  std::string line;
  std::ifstream myfile (std::string(ROOT_DIR) +"src/levels.txt");
  if (myfile.is_open())
  {
    getline(myfile, line);
    if(!line.compare("MAPS")){
      getline(myfile,line);
      this->obstacles.reserve(std::stof(line));
      getline(myfile,line);
      while (line.compare("/")){
        int length = 7;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Rectangle r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]));
        this->obstacles.push_back(r);
        delete [] valueArray;
        getline(myfile,line);
      }
    }
    getline(myfile,line);
    if(!line.compare("CHARACTER")){
      getline(myfile,line);
      while (line.compare("/")){
        int length = 9;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Character r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]), glm::vec2((valueArray[7]), valueArray[8]));
        this->character = r;
        delete [] valueArray;
        getline(myfile,line);
      }
    }
    myfile.close();
  }
  else{
    std::cout << "error open file !!" << std::endl;
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

Character Level::getCharacter(){
  return character;
}
std::vector<Rectangle> Level::getObstacles(){
  return obstacles;
}
