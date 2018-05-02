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

        cout << "list is len: " << chainLen << '\n';
        cout << "list has: \n" << tripsList[j] << "-----------------------\n";

        ChainIterator<nodeData> c;
        nodeData *x = c.Init(tripsList[j]);

        auto first = x;
        auto prev = x;
        auto next = (chainLen != 1) ? c.Next() : x;
        std::cout << "next has: " << *next << '\n';
        for (uint_fast16_t k = 0; k < chainLen; k++) {
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
          auto arriveTime = timeSpent[j] + prevNew;
          std::cout << "cur profit: " << curProfit << '\n';
          std::cout << "arrive: " << arriveTime << '\n';
          bool valid = isValidVisit(arriveTime, newNode.closeTime,
                                    newNode.openTime, newNode.visitDur);
          std::cout << "valid: " << valid << '\n';
          std::cout << "addTime: " << addTime << '\n';
          std::cout << "availableTime: " << availableTime[j] << '\n';
          std::cout << "max profit:" << maxProfit << '\n';
          if (curProfit > maxProfit && valid && addTime < availableTime[j]) {
            std::cout << "got in the loop if" << '\n';
            maxProfit = curProfit;
            insertAfter = k + 1;
            tourNum = j;
          }
          std::cout << "max profit:" << maxProfit << '\n';
          std::cout << "insertAfter:" << insertAfter << '\n';
          prev = next;
          next = (k + 2 != chainLen) ? c.Next() : first;
        }
      }
      std::cout << "before continue" << '\n';
      // get to the next vertice,could do not insert he last one nowhere
      if (tourNum == -1)
        continue;
      std::cout << "after continue" << '\n';

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
    std::cout << "STARTED DELETE" << '\n';
    for (uint_fast16_t d = 0; d < tours; d++) {
      std::cout << "START" << '\n';
      cout << "list is len: " << tripsList[d].Length() << '\n';
      cout << "Reached the end here are the trips:\n" << tripsList[d];
      std::cout << "next trips list---------------" << '\n';
      uint16_t listLen = tripsList[d].Length();
      std::cout << "in loop list len: " << listLen << '\n';
      if (listLen == 1)
        continue;
      auto randNodeNum = randomInt(1, listLen);
      auto test = randomFloat();
      std::cout << "rand float: " << test << '\n';
      auto nodesToDel = deleteNodesNum(test, listLen-1);
      std::cout << "random stuff: " << randNodeNum << " ::: " << nodesToDel << '\n';

      ChainIterator<nodeData> c;
      c.Init(tripsList[d]);

      nodeData *nextNode = nullptr;
      for (uint_fast16_t i = 1; i <= listLen; i++) {

        nextNode = c.Next();
        if (nextNode)
        std::cout << "in the listlen loop next node has \n" << *nextNode <<endl;
        if (i == randNodeNum) {
          if (nextNode)
          std::cout << "got in the if next node has \n" << *nextNode <<'\n';
          auto targetNode = nextNode;
          int deleted = 0;
          for (uint_fast16_t l = 0; l < nodesToDel && targetNode; l++) {
            // remove from list and free their memory
            uint16_t position = tripsList[d].Search(*targetNode);
            std::cout << "pos in the loop: " << position << '\n';
            std::cout << "before del\n" << tripsList[d] <<'\n';
            tripsList[d].Delete(position, *targetNode);
            std::cout << "after del\n" << tripsList[d] <<'\n';
            //delete targetNode;
            deleted++;
            targetNode = c.Next();
            if (targetNode)
            std::cout << "in the loop next node has \n" << *targetNode <<'\n';
          }

          std::cout << "deleted " << deleted << '\n';
          if (deleted != nodesToDel) {
            std::cout << "got in the if" << '\n';
            c.Init(tripsList[d]);
            auto remainingNode = c.Next();
            do {
              std::cout << "remain node has\n" << *remainingNode <<'\n';
              uint16_t position = tripsList[d].Search(*remainingNode);
              std::cout << "t has: " << position << '\n';
              std::cout << "before del\n" << tripsList[d] <<'\n';
              tripsList[d].Delete(position, *remainingNode);
              std::cout << "after del\n" << tripsList[d] <<'\n';
              //delete remainingNode;
              deleted++;

            } while ((remainingNode = c.Next()) && deleted < nodesToDel);

            break;
          } else {
            break;
          }
        }
      }
      std::cout << "END" << '\n';
      cout << "list is len: " << tripsList[d].Length() << '\n';
      cout << "Reached the end here are the trips:\n" << tripsList[d];
      std::cout << "next trips list---------------" << '\n';
    }
  }
  for (uint_fast16_t j = 0; j < tours; j++) {
    cout << "list is len: " << tripsList[j].Length() << '\n';
    cout << "Reached the end here are the trips:\n" << tripsList[j];
    std::cout << "next trips list---------------" << '\n';
  }
  //delete[] tripsList;
  delete[] timeSpent;
  delete[] availableTime;
  return 0;
}
