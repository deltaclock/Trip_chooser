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
  cout << "first 2 elements: " << txtArray[0] << "---------" << txtArray[1]
       << '\n';
  cout << "size of array is: " << txtArraySize << '\n';
  string *line1 = splitBySpace(txtArray[0], 16);
  // for (int_fast16_t i = 0; i < 15; i++) {
  //   cout << "value: " << line1[i] << '\n';
  // }

  uint16_t *line1Nums = firstLineToArray(line1);
  for (int_fast16_t i = 0; i < 3; i++) {
    cout << "value: " << line1Nums[i] << '\n';
  }
  return 0;
}
