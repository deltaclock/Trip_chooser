#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// converts the first line of the test file to array of ints
uint16_t *firstLineToArray(string *firstLine) {

  // store only the important dat in the array for efficiency
  uint16_t *intArray = new uint16_t[3];
  for (uint16_t i = 0; i < 3; i++) {
    intArray[i] = atoi(firstLine[i + 1].c_str());
  }

  return intArray;
}
