#include "parseFileV2.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Parse::Parse(const string *data, uint16_t linesNumber) {
  numberOfLines = linesNumber - 2;

  firstLineArray = new uint16_t[LINE_1_ARRAY_SIZE];
  secondLineArray = new uint16_t[LINE_2_ARRAY_SIZE];

  coordsDestinationArray = new float *[numberOfLines];

  for (uint_fast16_t i = 0; i < numberOfLines; i++) {
    coordsDestinationArray[i] = new float[FLOAT_ARRAY_SIZE];
  }

  dataLinesArray = new uint16_t *[numberOfLines];

  for (uint_fast16_t i = 0; i < numberOfLines; i++) {
    dataLinesArray[i] = new uint16_t[DATA_LINE_ARRAY_SIZE];
  }

  // store the data to the arrays
  convertFirstLine(data[0]);
  convertSecondLine(data[1]);
  convertRestLines(data, numberOfLines);
}

Parse::~Parse() {
  std::cout << "Deconstructor called!" << '\n';

  delete[] firstLineArray;
  delete[] secondLineArray;

  for (uint_fast16_t i = 0; i < numberOfLines; i++) {
    delete[] coordsDestinationArray[i];
  }
  delete[] coordsDestinationArray;

  for (uint_fast16_t i = 0; i < numberOfLines; i++) {
    delete[] dataLinesArray[i];
  }
  delete[] dataLinesArray;
}

void Parse::convertFirstLine(string firstLine) {
  istringstream strStream(firstLine);
  strStream.ignore(3);
  for (uint_fast16_t i = 0; i < 3; i++) {
    strStream >> firstLineArray[i];
  }
}

void Parse::convertSecondLine(string secondLine) {
  istringstream strStream(secondLine);
  strStream.ignore(2);
  // x,y coords
  strStream >> secondLineArray[0] >> secondLineArray[1];
  // start,end of tour
  strStream.ignore(5);
  strStream >> secondLineArray[2] >> secondLineArray[3];
}

void Parse::convertRestLines(const string *restOfLinesArray,
                             uint16_t arraySize) {
  for (uint_fast16_t j = 0; j < arraySize; j++) {

    istringstream strStream(restOfLinesArray[j + 2]);
    // vertex number
    strStream >> dataLinesArray[j][0];
    // x,y coords
    strStream >> coordsDestinationArray[j][0] >> coordsDestinationArray[j][1];
    // visiting duration - score of the location
    strStream >> dataLinesArray[j][1] >> dataLinesArray[j][2];
    strStream.ignore(3);
    // stores opening and closing hour of the day to the array
    for (uint_fast16_t i = 3; i < 17; i++) {
      strStream >> dataLinesArray[j][i];
    }
  }
}
