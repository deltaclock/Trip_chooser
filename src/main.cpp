#include "parseFile.hpp"
#include "storeFile.hpp"
#include "stringUtils.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
  string testFile;
  cin >> testFile;
  string *txtArray;
  int txtArraySize = fileToArray(testFile, &txtArray);
  cout << "first 2 elements: " << txtArray[0] << "-----" << txtArray[1] << '\n';
  cout << "size of array is: " << txtArraySize << '\n';
  string *line1 = splitBySpace(txtArray[0], 16);
  string *line2 = splitBySpace(txtArray[1], 7);
  string *line3 = splitBySpace(txtArray[2], 21);

  uint16_t *line1Nums = convertFirstLine(line1);
  uint16_t *line2Nums = convertSecondLine(line2);
  for (int_fast16_t i = 0; i < 3; i++) {
    cout << "value line1: " << line1Nums[i] << '\n';
  }
  for (int_fast16_t i = 0; i < 4; i++) {
    cout << "value line2: " << line2Nums[i] << '\n';
  }
  float *coords;
  uint16_t *line3Nums = convertRestLines(line3, &coords);

  for (int_fast16_t i = 0; i < 2; i++) {
    cout << "coords: " << coords[i] << '\n';
  }
  for (int_fast16_t i = 0; i < 17; i++) {
    cout << "value line3: " << line3Nums[i] << '\n';
  }

  //delete all arrays from heap
  delete[] txtArray;
  delete[] line1;
  delete[] line2;
  delete[] line3;
  delete[] line1Nums;
  delete[] line2Nums;
  delete[] line3Nums;
  delete[] coords;

  return 0;
}
