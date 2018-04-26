#include "storeFileV2.hpp"
#include <sstream>
#include <iostream>

using namespace std;

Store::Store(string file) {
  fileName = file;
  openFile();
  calcNumberOfLines();
  // init string array to hold each line
  resultArray = new string[numberOfLines];
 }

Store::~Store() {
  cout << "stuff should get deleted" << '\n';
  delete[] resultArray;
  dataFile.close();
}

string *Store::getFileArray() {
  string line;
  for (uint16_t i = 0; i < numberOfLines && getline(dataFile, line); i++) {
    // add dataFile.good() check?
    resultArray[i] = line;
  }

  return resultArray;
}

void Store::openFile(){
  dataFile.open(fileName);
  if (!dataFile.is_open()) {
    throw ios_base::failure("Failed to open file!");
  }
}

void Store::calcNumberOfLines(){
  // get total num of lines based on the vertices number on the first line
  string line;
  getline(dataFile, line);
  istringstream firstLine(line);
  firstLine.ignore(7);
  firstLine >> numberOfLines;
  numberOfLines += 2;

  // clear the eof flag
  dataFile.clear();
  dataFile.seekg(0, ios::beg);
}
