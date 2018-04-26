#ifndef PARSE_FILE_V2_HPP
#define PARSE_FILE_V2_HPP
#include <string>

using namespace std;

class Parse {
private:
  const uint_fast16_t LINE_1_ARRAY_SIZE = 3;
  const uint_fast16_t LINE_2_ARRAY_SIZE = 4;
  const uint_fast16_t FLOAT_ARRAY_SIZE = 2;
  const uint_fast16_t DATA_LINE_ARRAY_SIZE = 17;
  void convertFirstLine(string firstLine);
  void convertSecondLine(string secondLine);
  void convertRestLines(const string *restOfLinesArray, uint16_t arraySize);

public:
  uint16_t numberOfLines = 0;
  uint16_t *firstLineArray = nullptr;
  uint16_t *secondLineArray = nullptr;
  uint16_t **dataLinesArray = nullptr;
  float **coordsDestinationArray = nullptr;

  Parse(const string *data, uint16_t linesNumber);
  ~Parse();

};

#endif
