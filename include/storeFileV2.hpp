#ifndef STORE_FILE_V2_HPP
#define STORE_FILE_V2_HPP
#include <string>
#include <fstream>

using namespace std;

class Store {
private:
  string fileName;
  string *resultArray;
  ifstream dataFile;
  void openFile();
  void calcNumberOfLines();

public:
  uint16_t numberOfLines = 0;
  Store(string file);
  ~Store();

  string *getFileArray();
};
#endif
