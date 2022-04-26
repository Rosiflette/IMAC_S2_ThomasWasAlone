#include "Level.h"
#include "Constants.h"

#include <fstream>


Level::Level(){
  std::cout << "Test" << std::endl;
  this->obstaclesLength = 0;
  char delimiter = ';';
  std::string line;
  std::ifstream myfile ("levels.txt");
  if (myfile.is_open())
  {
    while ( getline(myfile,line) )
    {
      int length = 7;
      float* valueArray = new float [length];
      split(line, delimiter, valueArray, length);
      Rectangle r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]));
      this->obstacles[obstaclesLength] = r;
      this->obstaclesLength++;
      delete [] valueArray;
    }
    myfile.close();
  }
  else{
    std::cout << "error !!" << std::endl;
  }
}

void Level::split(std::string line, char delimiter, float arr[], int length){
  std::string val;
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != std::string::npos) { // npos => quand il n'y a pas eu de delimmiter trouvé
      val = line.substr(0, pos);
      arr[length] = std::stof(val);
      length++;
      std::cout << "val : " << arr[length--] << std::endl;
      line.erase(0, pos + 1);
  }
}
