#include "chain.hpp"
#include "chainBasic.cpp"
#include "chainInsert.cpp"
#include "chainFind.cpp"
#include "logic.hpp"
#include "node.hpp"
#include "parseFileV2.hpp"
#include "storeFile.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <repeats> "
         << "<filepath>\n";
    return 1;
  }
  int_fast16_t repeats = atoi(argv[1]);
  string file(argv[2]);
  string *txtArray;
  int txtArraySize = 0;
  try{
    txtArraySize = fileToArray(file, &txtArray);
  }catch(const ios_base::failure& ex){
    cerr << "Could not open file!!" << '\n';
    return 1;
  }
  Parse obj(txtArray, txtArraySize);

  delete[] txtArray;

  nodeData hotel = makeHotel(obj);

  auto tours = obj.firstLineArray[0];
  auto day = obj.firstLineArray[1];
  cout << "tours: " << tours << '\n';

  Chain<nodeData> *tripsList = new Chain<nodeData>[tours];
  uint16_t *timeSpent = new uint16_t[tours];
  uint16_t *availableTime = new uint16_t[tours];

  for (uint_fast16_t j = 0; j < tours; j++) {
    tripsList[j].Append(hotel);
    availableTime[j] = hotel.closeTime - hotel.openTime;
    timeSpent[j] = hotel.openTime;
  }

  for (int_fast16_t e = 0; e < repeats; e++) {
    for (int_fast16_t i = 0; i < obj.numberOfVertices; i++) {

      float maxProfit = -1;
      int16_t insertAfter = -1;
      int16_t tourNum = -1;
      for (uint_fast16_t j = 0; j < tours; j++) {

        nodeData newNode = makeSight(obj, i, day, j);
        auto chainLen = tripsList[j].Length();

        ChainIterator<nodeData> c;
        nodeData *x = c.Init(tripsList[j]);

        auto first = x;
        auto prev = x;
        auto next = (chainLen != 1) ? c.Next() : x;
        for (uint_fast16_t k = 0; k < chainLen; k++) {

          auto prevNext = pointsDistance(prev->xcoord, prev->ycoord,
                                         next->xcoord, next->ycoord);
          auto prevNew = pointsDistance(prev->xcoord, prev->ycoord,
                                        newNode.xcoord, newNode.ycoord);

          auto newNext = pointsDistance(next->xcoord, next->ycoord,
                                        newNode.xcoord, newNode.ycoord);

          float curProfit = profit(newNode.score, newNode.visitDur, prevNew,
                                   newNext, prevNext);
          auto addTime = additionalTime(curProfit, newNode.score);
          auto arriveTime = timeSpent[j] + prevNew;

          bool valid = isValidVisit(arriveTime, newNode.closeTime,
                                    newNode.openTime, newNode.visitDur);

          if (curProfit > maxProfit && valid && addTime < availableTime[j]) {
            maxProfit = curProfit;
            insertAfter = k + 1;
            tourNum = j;
          }
          prev = next;
          next = (k + 2 != chainLen) ? c.Next() : first;
        }
      }
      // get to the next vertice,could do not insert the last one nowhere
      if (tourNum == -1)
        continue;

      // make the sight to be inserted.
      auto sight = makeSight(obj, i, day, tourNum);
      if (insertAfter == tripsList[tourNum].Length()) {
        tripsList[tourNum].Append(sight);
      } else {
        tripsList[tourNum].Insert(insertAfter, sight);
      }
      // if it reached here insertion is done, adjust times.
      auto addTime = additionalTime(maxProfit, sight.score);
      timeSpent[tourNum] += addTime;
      availableTime[tourNum] -= addTime;
    }
    // loop the trips chain lists
    for (uint_fast16_t d = 0; d < tours; d++) {

      uint16_t listLen = tripsList[d].Length();
      if (listLen == 1)
        continue;
      auto randNodeNum = randomInt(1, listLen);
      auto nodesToDel = deleteNodesNum(randomFloat(), listLen-1);
      ChainIterator<nodeData> c;
      c.Init(tripsList[d]);

      nodeData *nextNode = nullptr;
      for (uint_fast16_t i = 1; i <= listLen && i -1 != randNodeNum; i++) {

        nextNode = c.Next();
        if (i == randNodeNum) {
          auto targetNode = nextNode;
          uint_fast16_t deleted;
          for (deleted = 0; deleted < nodesToDel && targetNode; deleted++) {
            // remove from list and free their memory
            uint16_t position = tripsList[d].Search(*targetNode);
            tripsList[d].Delete(position, *targetNode);
            targetNode = c.Next();
          }

          if (deleted != nodesToDel) {
            c.Init(tripsList[d]);
            auto remainingNode = c.Next();
            for (; deleted < nodesToDel; deleted++){

              uint16_t position = tripsList[d].Search(*remainingNode);
              tripsList[d].Delete(position, *remainingNode);
              remainingNode = c.Next();
            }
          }
        }
      }
    }
  }
  std::cout << "--------------------------LAST PRINT-----------------------------" << '\n';
  for (uint_fast16_t j = 0; j < tours; j++) {
    cout << "list is len: " << tripsList[j].Length() << '\n';
    cout << "Reached the end here are the trips:\n" << tripsList[j];
    std::cout << "next trips list---------------" << '\n';
  }
  delete[] tripsList;
  delete[] timeSpent;
  delete[] availableTime;
  return 0;
}
