#include <cmath>
#include <iostream>

using namespace std;

float pointsDistance(float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0) {

  float t0 = pow((x1 - x2), 2);             // (x1-x2)^2
  float t1 = pow((y1 - y2), 2);             // (y1-y2)^2
  return floorf(sqrt(t0 + t1) * 100) / 100; // square root and floor to 2nd dec
}

float profit(uint16_t score, uint16_t visitDuration, float distancePrevCurr,
             float distanceNextCurr, float distancePrevNext) {

  return pow(score, 2) / (visitDuration + distancePrevCurr + distanceNextCurr -
                          distancePrevNext);
}

bool isValidVisit(uint16_t arrival, uint16_t closingTime, uint16_t openingTime,
                  uint16_t averageTime) {
  return (openingTime <= arrival && arrival < closingTime &&
          arrival + averageTime < closingTime);
}


//
// int main(int argc, char const *argv[]) {
//
//   cout << "distance:  " << pointsDistance(2.3, 5.6, 7.8, 4.6) << '\n';
//   cout << "profit: " << profit(10, 40, 5.89, 6.78, 7.43) << '\n';
//   return 0;
// }
