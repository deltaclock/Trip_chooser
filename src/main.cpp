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

  auto tours = obj.firstLineArray[0];
  auto day = obj.firstLineArray[1];
  cout << "tours: " << tours << '\n';

  Chain<nodeData> L;
  L.Append(hotel);

  cout << "list is len: " << L.Length() << '\n';
  cout << "list has: " << L;

  for (uint_fast16_t i = 0; i < 2; i++) {
    for (uint_fast16_t j = 0; j < tours; j++) {
      nodeData sight;
      sight.vertexNum = obj.dataLinesArray[i][0];
      sight.xcoord = obj.coordsDestinationArray[i][0];
      sight.ycoord = obj.coordsDestinationArray[i][1];
      sight.visitDur = obj.dataLinesArray[i][1];
      sight.score = obj.dataLinesArray[i][2];
      sight.openTime = obj.dataLinesArray[i][3 + day + j];
      sight.closeTime = obj.dataLinesArray[i][4 + day + j];

      L.Append(sight);
      cout << "list is len: " << L.Length() << '\n';
      cout << "list has: \n" << L << "\n-------------------------------------\n";
      ChainIterator<nodeData> c;
      nodeData *x = c.Init(L);

      do {
        cout << *x << endl;
      } while ((x = c.Next()));
    }
  }

  return 0;
}
