#include <sstream>
#include <string>

using namespace std;

// splits a string by space and stores the result in an array of lenght
// numOfWords
string *splitBySpace(string sourceStr, uint_fast16_t numOfWords = 1) {
  istringstream inputStr(sourceStr);
  string outputStr;
  string *outputArray = new string[numOfWords];

  for (uint_fast16_t i = 0; i < numOfWords  && getline(inputStr, outputStr, ' ');
       i++) {
    outputArray[i] = outputStr;
  }

  return outputArray;
}
