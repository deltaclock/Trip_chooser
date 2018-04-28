#include "chain.hpp"
#include "chainBasic.cpp"
#include "node.hpp"
#include "parseFileV2.hpp"
#include "storeFile.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  string testFile;
  cin >> testFile;
  string *txtArray;
  int txtArraySize = fileToArray(testFile, &txtArray);

  // std::cout << "numlines " << txtArraySize << '\n';
  Parse obj(txtArray, txtArraySize);

  delete[] txtArray;

  nodeData hotel;
  hotel.xcoord = obj.secondLineArray[0];
  hotel.ycoord = obj.secondLineArray[1];
  hotel.openTime = obj.secondLineArray[2];
  hotel.closeTime = obj.secondLineArray[3];

  // uint16_t *line1Nums = obj.firstLineArray;
  // uint16_t *line2Nums = obj.secondLineArray;

  cout << "tours: " << obj.firstLineArray[0] << '\n';
  Chain<nodeData> L;
  L.Append(hotel);

  cout << "list is len: " << L.Length() << '\n';
  cout << "list has: " << L;

  // for (int_fast16_t i = 0; i < 3; i++) {
  //   cout << "value line1: " << line1Nums[i] << '\n';
  // }
  // for (int_fast16_t i = 0; i < 4; i++) {
  //   cout << "value line2: " << line2Nums[i] << '\n';
  // }

  // float **coords = obj.coordsDestinationArray;
  // uint16_t **line3Nums = obj.dataLinesArray;
  //
  // for (uint_fast16_t j = 0; j < obj.numberOfLines; j++) {
  //
  //   for (int_fast16_t i = 0; i < 2; i++) {
  //     cout << "coords: " << coords[j][i] << '\n';
  //     cout << " type: " << typeid(coords[j][i]).name() << '\n';
  //   }
  //   for (int_fast16_t i = 0; i < 17; i++) {
  //     cout << "value line3: " << line3Nums[j][i] << '\n';
  //     cout << "value line3 type: " << typeid(line3Nums[j][i]).name() << '\n';
  //   }
  // }
  return 0;
}
