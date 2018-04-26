#include <fstream>
#include <sstream>
#include <string>

using namespace std;

uint16_t fileToArray(string fileName, string **destinationArray) {
  uint16_t linesNumber = 0;
  ifstream dataFile(fileName);
  if (!dataFile.is_open()) {
    throw ios_base::failure("Failed to open file!");
  }

  // get total num of lines based on the vertices number on the first line
  string line;
  getline(dataFile, line);
  istringstream firstLine(line);
  firstLine.ignore(7);
  firstLine >> linesNumber;
  linesNumber += 2;

  // init string array to hold each line
  *destinationArray = new string[linesNumber];
  // clear the eof flag
  dataFile.clear();
  dataFile.seekg(0, ios::beg);
  for (uint16_t i = 0; i < linesNumber && getline(dataFile, line); i++) {
    // add dataFile.good() check?
    (*destinationArray)[i] = line;
  }
  dataFile.close();
  return linesNumber;
}
