#include "chain.hpp"
#include "chainBasic.cpp"
#include "chainInsert.cpp"
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
  cout << repeats;
  string file(argv[2]);
  string *txtArray;
  int txtArraySize = fileToArray(file, &txtArray);

  Parse obj(txtArray, txtArraySize);

  delete[] txtArray;

  nodeData hotel = makeHotel(obj);

  auto availableTime = hotel.closeTime - hotel.openTime;
  auto timeSpent = hotel.openTime;
  auto tours = obj.firstLineArray[0];
  auto day = obj.firstLineArray[1];
  cout << "tours: " << tours << '\n';

  Chain<nodeData> *tripsList = new Chain<nodeData>[tours];

  for (uint_fast16_t j = 0; j < tours; j++) {
    tripsList[j].Append(hotel);
  }

  for (int_fast16_t e = 0; e < repeats; e++) {
    for (int_fast16_t i = 0; i < obj.numberOfVertices; i++) {
      for (uint_fast16_t j = 0; j < tours; j++) {
        nodeData sight = makeSight(obj, i, day, j);

        cout << "list is len: " << tripsList[j].Length() << '\n';
        cout << "list has: \n" << tripsList[j] << "\n-----------------------\n";

        ChainIterator<nodeData> c;
        nodeData *x = c.Init(tripsList[j]);

        float maxProfit = -1;
        int16_t insertAfter = -1;
        auto first = x;
        auto prev = x;
        auto newNode = sight;
        auto next = (tripsList[j].Length() != 1) ? c.Next() : x;
        std::cout << "next has: " << *next << '\n';
        for (uint_fast16_t k = 0; k < tripsList[j].Length(); k++) {
          std::cout << "got in the third loop" << '\n';
          std::cout << "next has: " << *next << '\n';
          std::cout << "prev has: " << *prev << '\n';
          auto prevNext = pointsDistance(prev->xcoord, prev->ycoord,
                                         next->xcoord, next->ycoord);
          auto prevNew = pointsDistance(prev->xcoord, prev->ycoord,
                                        newNode.xcoord, newNode.ycoord);

          auto newNext = pointsDistance(next->xcoord, next->ycoord,
                                        newNode.xcoord, newNode.ycoord);

          float curProfit = profit(newNode.score, newNode.visitDur, prevNew,
                                   newNext, prevNext);
          auto addTime = additionalTime(curProfit, newNode.score);
          auto arriveTime = timeSpent + prevNew;
          std::cout << "cur profit: " << curProfit << '\n';
          std::cout << "arrive: " << arriveTime << '\n';
          bool valid = isValidVisit(arriveTime, newNode.closeTime,
                                    newNode.openTime, newNode.visitDur);
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
          next = (k + 2 != tripsList[j].Length()) ? c.Next() : first;
        }

        std::cout << "before continue" << '\n';
        if (insertAfter == -1)
          continue;
        std::cout << "after continue" << '\n';

        if (insertAfter == tripsList[j].Length()) {
          tripsList[j].Append(sight);
        } else {
          tripsList[j].Insert(insertAfter, sight);
        }
        // if it reached here insertion is done, adjust times.
        auto addTime = additionalTime(maxProfit, sight.score);
        timeSpent += addTime;
        availableTime -= addTime;
      }
    }
    // TODO DELETE NODES
  }
  for (uint_fast16_t j = 0; j < tours; j++) {
    cout << "list is len: " << tripsList[j].Length() << '\n';
    cout << "Reached the end here are the trips:\n" << tripsList[j];
  }

  return 0;
}
