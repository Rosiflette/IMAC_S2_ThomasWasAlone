#include "Reader.h"

Reader::Reader(std::string file){
    myfile.open(file);
    if(!myfile.is_open()){
    std::cout << "Fichier mal ouvert" << std::endl;
  }
}


Level Reader::readNextLevel(){
  Level lvl;
  std::string line;
  char delimiter = ';';
  while(getline(this->myfile, line) && line.compare("/")){
    switch (line[0]) {
      case 'm':
      {
        line = line.substr(1, line.length());
        int length = 7;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Rectangle r (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]));
        lvl.addObsacles(r);
        delete [] valueArray;
        break;
      }

      case 'c':
      {
        line = line.substr(1, line.length());
        int length = 9;
        float* valueArray = new float [length];
        split(line, delimiter, valueArray);
        Character c (glm::vec2(valueArray[0],valueArray[1]),valueArray[2],valueArray[3],glm::vec3(valueArray[4],valueArray[5],valueArray[6]), glm::vec2((valueArray[7]), valueArray[8]));
        lvl.setCharacter(c);
        delete [] valueArray;
        break;}
      default:
        std::cout << "Elément non reconnu dans la lecture du fichier" << std::endl;

    }

  }
  return lvl;
}


void Reader::split(std::string line, char delimiter, float arr[]){
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
