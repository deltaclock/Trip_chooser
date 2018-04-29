#include <cmath>
#include "logic.hpp"

using namespace std;

float pointsDistance(float x1, float y1, float x2, float y2) {

  float t0 = pow((x1 - x2), 2);             // (x1-x2)^2
  float t1 = pow((y1 - y2), 2);             // (y1-y2)^2
  return floorf(sqrt(t0 + t1) * 100) / 100; // square root and floor to 2nd dec
}

float profit(uint16_t score, uint16_t visitDuration, float distancePrevNew,
             float distanceNextNew, float distancePrevNext) {

  return pow(score, 2) / (visitDuration + distancePrevNew + distanceNextNew -
                          distancePrevNext);
}

bool isValidVisit(uint16_t arrival, uint16_t closingTime, uint16_t openingTime,
                  uint16_t averageTime) {
  return (openingTime <= arrival && arrival < closingTime &&
          arrival + averageTime < closingTime);
}

float additionalTime(float profit, uint16_t score) {
  return pow(score, 2) / profit;
}
