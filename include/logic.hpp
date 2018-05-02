#ifndef LOGIC_HPP
#define LOGIC_HPP
#include <iostream>
float pointsDistance(float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0);
float profit(uint16_t score, uint16_t visitDuration, float distancePrevCurr,
             float distanceNextCurr, float distancePrevNext);

bool isValidVisit(uint16_t arrival, uint16_t closingTime, uint16_t openingTime,
                  uint16_t averageTime);
float additionalTime(float profit, uint16_t score);
uint16_t randomInt(uint16_t minN, uint16_t maxN);
float randomFloat();
uint16_t deleteNodesNum(float randN, uint16_t chainLen);
#endif
