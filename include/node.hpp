#ifndef NODE_HPP
#define NODE_HPP
#include "parseFileV2.hpp"
#include <iostream>

typedef struct nodeData {

  uint16_t vertexNum = 0;
  float xcoord = 0.0;
  float ycoord = 0.0;
  uint16_t visitDur = 0;
  uint16_t score = 0;
  uint16_t openTime = 0;
  uint16_t closeTime = 0;

  friend std::ostream &operator<<(std::ostream &os, nodeData const &nd) {
    return os << nd.vertexNum << '\t' << nd.xcoord << '\t' << nd.ycoord << '\t'
              << nd.visitDur << '\t' << nd.score << '\t' << nd.openTime << '\t'
              << nd.closeTime << '\t';
  }
} nodeData;
inline bool operator!=(const nodeData &lhs, const nodeData &rhs) {
  return lhs.vertexNum != rhs.vertexNum;
}
nodeData makeHotel(const Parse &o);
nodeData makeSight(const Parse &o, uint16_t vertex, uint16_t day, uint16_t t);
#endif
