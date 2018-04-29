#include "chain.hpp"
#include "chainBasic.cpp"
#include "chainInsert.cpp"
#include "logic.hpp"
#include "node.hpp"
#include "parseFileV2.hpp"
#include "storeFile.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  string testFile;
  cin >> testFile;
  string *txtArray;
  int txtArraySize = fileToArray(testFile, &txtArray);

  Parse obj(txtArray, txtArraySize);

  delete[] txtArray;

  nodeData hotel = makeHotel(obj);

  auto availableTime = hotel.closeTime - hotel.openTime;
  auto timeSpent = hotel.openTime;
  auto tours = obj.firstLineArray[0];
  auto day = obj.firstLineArray[1];
  cout << "tours: " << tours << '\n';

  Chain<nodeData> *tripsList = new Chain<nodeData>[tours];

  tripsList[0].Append(hotel);
  // check if we can really add those?????
  // for (uint_fast16_t i = 0; i < tours; i++) {
  //   nodeData firstSight = makeSight(obj, i, day, i);
  //   tripsList[i].Append(firstSight);
  //   timeSpent += firstSight.visitDur;
  // }

  // cout << "list is len: " << tripsList[0].Length() << '\n';
  // cout << "list has: " << tripsList[0];

  for (int_fast16_t i = 0; i < obj.numberOfVertices; i++) {
    for (uint_fast16_t j = 0; j < tours; j++) {

      nodeData sight = makeSight(obj, i, day, j);

      cout << "list is len: " << tripsList[0].Length() << '\n';
      cout << "list has: \n" << tripsList[0] << "\n-----------------------\n";

      ChainIterator<nodeData> c;
      nodeData *x = c.Init(tripsList[0]);

      float maxProfit = -1;
      int16_t insertAfter = -1;
      auto first = x;
      auto prev = x;
      auto newNode = sight;
      auto next = (tripsList[0].Length() != 1) ? c.Next() : x;
      std::cout << "next has: " << *next << '\n';
      for (uint_fast16_t k = 0; k < tripsList[0].Length(); k++) {
        std::cout << "got in the third loop" << '\n';
        std::cout << "next is: " << next << '\n';
        auto prevNext = pointsDistance(prev->xcoord, prev->ycoord, next->xcoord,
                                       next->ycoord);
        auto prevNew = pointsDistance(prev->xcoord, prev->ycoord,
                                      newNode.xcoord, newNode.ycoord);

        auto newNext = pointsDistance(next->xcoord, next->ycoord,
                                      newNode.xcoord, newNode.ycoord);

        float curProfit =
            profit(newNode.score, newNode.visitDur, prevNew, newNext, prevNext);
        auto addTime = additionalTime(curProfit, newNode.score);
        auto arriveTime = timeSpent + prevNew;
        std::cout << "cur profit: " << curProfit << '\n';
        bool valid = isValidVisit(arriveTime, newNode.openTime,
                                  newNode.closeTime, newNode.visitDur);
        std::cout << "valid: " << valid << '\n';
        std::cout << "addTime: " << addTime << '\n';
        std::cout << "availableTime: " << availableTime << '\n';
        std::cout << "max profit:" << maxProfit << '\n';
        if (curProfit > maxProfit && valid && addTime < availableTime) {
          std::cout << "got in the loop if" << '\n';
          maxProfit = curProfit;
          insertAfter = k + 1;
        }
        std::cout << "max profit:" << maxProfit << '\n';
        std::cout << "insertAfter:" << insertAfter << '\n';
        prev = next;
        next = (k + 2 != tripsList[0].Length()) ? c.Next() : first;
      }
      // calc first-last stuff
      auto prevNext = pointsDistance(prev->xcoord, prev->ycoord, first->xcoord,
                                     first->ycoord);
      auto prevNew = pointsDistance(prev->xcoord, prev->ycoord, newNode.xcoord,
                                    newNode.ycoord);

      auto newNext = pointsDistance(first->xcoord, first->ycoord,
                                    newNode.xcoord, newNode.ycoord);

      float curProfit =
          profit(newNode.score, newNode.visitDur, prevNew, newNext, prevNext);
      auto addTime = additionalTime(curProfit, newNode.score);
      auto arriveTime = timeSpent + prevNew;

      if (curProfit > maxProfit &&
          isValidVisit(arriveTime, newNode.openTime, newNode.closeTime,
                       newNode.visitDur) &&
          addTime < availableTime) {

        maxProfit = curProfit;
        insertAfter = tripsList[0].Length();
      }
      std::cout << "before continue" << '\n';
      if (insertAfter == -1)
        continue;
      std::cout << "after continue" << '\n';

      if (insertAfter == tripsList[0].Length()) {
        tripsList[0].Append(sight);
      } else {
        tripsList[0].Insert(insertAfter, sight);
      }
      // if it reached here insertion is done, adjust times.
      addTime = additionalTime(maxProfit, sight.score);
      timeSpent += addTime;
      availableTime -= addTime;
    }
  }
  cout << "list is len: " << tripsList[0].Length() << '\n';
  cout << "Reached the end here are the trips:\n" << tripsList[0];

  return 0;
}
