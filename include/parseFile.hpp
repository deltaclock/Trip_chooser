#include <string>
#ifndef PARSE_FILE_HPP
#define PARSE_FILE_HPP
uint16_t *convertFirstLine(std::string *firstLine);
uint16_t *convertSecondLine(std::string *secondLine);
uint16_t *convertRestLines(std::string *dataLine, float **coordsDestinationArray);
#endif
