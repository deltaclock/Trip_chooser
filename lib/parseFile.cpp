#include <iostream>
#include <sstream>
#include <string>
//TODO  makes this a class to denconstruct arrays ;)
using namespace std;
// All of the funcs need a string array, so they can convert the data

// converts the first line of the test file to array of ints
uint16_t *convertFirstLine(string *firstLine) {

  // store only the important data in the array for efficiency
  uint16_t *intArray = new uint16_t[3];
  for (uint16_t i = 0; i < 3; i++) {
    intArray[i] = atoi(firstLine[i + 1].c_str());
  }

  return intArray;
}

// converts the second line of the test file to array of ints
uint16_t *convertSecondLine(string *secondLine) {

  // store only the important data in the array for efficiency
  uint16_t *intArray = new uint16_t[4];

  intArray[0] = atoi(secondLine[1].c_str()); // x coordinate
  intArray[1] = atoi(secondLine[2].c_str()); // y coordinate
  intArray[2] = atoi(secondLine[5].c_str()); // start of the tour
  intArray[3] = atoi(secondLine[6].c_str()); // end of the tour

  return intArray;
}

// returns an int array for each point's data and a stores the coordinates in
// the coordsDestinationArray parameter
uint16_t *convertRestLines(string *dataLine, float **coordsDestinationArray) {

  uint16_t *dataIntArray = new uint16_t[17];
  *coordsDestinationArray = new float[2];

  dataIntArray[0] = atoi(dataLine[0].c_str()); // vertex number
  (*coordsDestinationArray)[0] = strtof(dataLine[1].c_str(), 0); // x coordinate
  (*coordsDestinationArray)[1] = strtof(dataLine[2].c_str(), 0); // y coordinate
  dataIntArray[1] = atoi(dataLine[3].c_str()); // visiting duration
  dataIntArray[2] = atoi(dataLine[4].c_str()); // score of the location

  //stores opening and closing hour of the day to the array
  for (uint_fast16_t j = 3; j < 17; j++) {
    dataIntArray[j] = atoi(dataLine[j + 3].c_str());
  }

  return dataIntArray;
}
