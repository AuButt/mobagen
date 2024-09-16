#include "JohnConway.h"


// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for(int y = 0; y <= world.SideSize(); y++) {
    for(int x = 0; x <= world.SideSize(); x++) {
      Point2D p = Point2D(x,y);

      //if the cell is populated (adds one because countneighbors includes itself if the cell is populated)
      if(world.Get(p) == true) {
        //kill unit solitude
        if(CountNeighbors(world, p) <= 2) {
          world.SetNext(p, false);
        }
        //kill unit overpopulation
        if(CountNeighbors(world, p) >= 5) {
          world.SetNext(p, false);
        }
        if(CountNeighbors(world, p) == 3 || CountNeighbors(world, p) == 4) {
          world.SetNext(p, true);
        }
      }
      //if the cell is empty
      else {
        //make unit
        if(CountNeighbors(world, p) == 3) {
          world.SetNext(p, true);
        }
      }
    }
  }
}


int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int acc = 0;
  for(int y = -1; y <= 1; y++) {
    for(int x = -1; x <= 1; x++) {
      Point2D p = point + Point2D(x, y);
      acc += world.Get(p);
    }
  }
  return acc;
}
