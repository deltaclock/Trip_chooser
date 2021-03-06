#include "node.hpp"

nodeData makeHotel(const Parse &o) {
  nodeData tmpHotel;
  tmpHotel.xcoord = o.secondLineArray[0];
  tmpHotel.ycoord = o.secondLineArray[1];
  tmpHotel.openTime = o.secondLineArray[2];
  tmpHotel.closeTime = o.secondLineArray[3];

  return tmpHotel;
}

nodeData makeSight(const Parse &o, uint16_t vertex, uint16_t day, uint16_t t) {
  day = (day + t > 6) ? t - (7 - day) : day;

  nodeData tmpSight;
  tmpSight.vertexNum = o.dataLinesArray[vertex][0];
  tmpSight.xcoord = o.coordsDestinationArray[vertex][0];
  tmpSight.ycoord = o.coordsDestinationArray[vertex][1];
  tmpSight.visitDur = o.dataLinesArray[vertex][1];
  tmpSight.score = o.dataLinesArray[vertex][2];
  tmpSight.openTime = o.dataLinesArray[vertex][3 + day * 2 + t];
  tmpSight.closeTime = o.dataLinesArray[vertex][4 + day * 2 + t];

  return tmpSight;
}
