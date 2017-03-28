#ifndef __SCANNER__
#define __SCANNER__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Scanner
{
private:
  char * fileBuffer;
  string filename;
  int currentFileIndex;
  size_t fileSize;
  void printMagic(string signature);
  bool filterTAR;
public:
  Scanner(string filename);
  ~Scanner();
  void scan();
};


#endif
