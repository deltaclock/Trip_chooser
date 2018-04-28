#include <iostream>

typedef struct nodeData {

  uint16_t vertexNum = 0;
  float xcoord;
  float ycoord;
  uint16_t visitDur = 0;
  uint16_t score = 0;
  uint16_t openTime;
  uint16_t closeTime;

  friend std::ostream& operator <<(std::ostream& os, nodeData const& nd)
    {
        return os << nd.vertexNum << '\t'
                  << nd.xcoord << '\t'
                  << nd.ycoord << '\t'
                  << nd.visitDur << '\t'
                  << nd.score << '\t'
                  << nd.openTime << '\t'
                  << nd.closeTime << '\t';
    }
} nodeData;
