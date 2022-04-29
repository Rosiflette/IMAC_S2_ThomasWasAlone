#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include "Level.h"

class Reader{
  private :
    std::ifstream myfile;

  public :
    Reader(std::string file);

    Level readNextLevel();
    void split(std::string line, char delimiter, float arr[]);



};


#endif // READER_H
