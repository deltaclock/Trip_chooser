#include <fstream>
#include <iostream>
#include <string>

using namespace std;

uint16_t fileToArray(string fileName, string **destinationArray) {
  uint16_t linesNumber = 0;
  ifstream dataFile(fileName);
  if (!dataFile.is_open()) {
    throw ios_base::failure("Failed to open file!");
  }
  string line;
  while (getline(dataFile, line))
    ++linesNumber;

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

// int main() {
//   string testFile;
//   string *txtArray;
//   cin >> testFile;
//   int txtArraySize = fileToArray(testFile, &txtArray);
//   cout << "first 2 elements: " << txtArray[0] << " " << txtArray[1] << '\n';
//   cout << "size of array is: " << txtArraySize << '\n';
//   for (int j = 0; j < txtArraySize; j++) {
//     cout << txtArray[j] << '\n';
//   }
//   delete[] txtArray;
// }
