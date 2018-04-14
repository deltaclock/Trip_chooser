#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int fileToArray(string fileName, string **destinationArray) {
  unsigned short linesNumber = 0; // unsigned int_fast16_t ?
  ifstream dataFile(fileName);
  if (!dataFile.is_open()) {
    throw ios_base::failure("Failed to open file!");
  }
  string line;
  while (getline(dataFile, line)) {
    // add dataFile.good() check?
    ++linesNumber;
  }
  // init string array to hold each line
  *destinationArray = new string[linesNumber];
  // clear the eof flag
  dataFile.clear();
  dataFile.seekg(0, ios::beg);
  for (unsigned short i = 0; i < linesNumber && getline(dataFile, line); i++) {
    // add dataFile.good() check?
    (*destinationArray)[i] = line;
  }
  dataFile.close();
  return linesNumber;
}

int main() {
  string testFile;
  string* txtArray;
  cin >> testFile;
  int txtArraySize = fileToArray(testFile, &txtArray);
  cout << "first 2 elements: " << txtArray[0] << " " << txtArray[1] << '\n';
  cout << "size of array is: " << txtArraySize << '\n';
  for (int j = 0; j < txtArraySize; j++) {
    cout << txtArray[j] << '\n';
  }
}
