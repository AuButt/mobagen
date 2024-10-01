#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <stack>

int i = 0;
int rands[] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
std::stack<Point2D> stack;

bool RecursiveBacktrackerExample::Step(World* w) {
  //walls up
  //add top left to stack
  if(i == 0) {
    stack.push_back(Point2D(0, 0));
  }

  //while stack empty
  if (!stack.empty()) {
    std::vector<Point2D> neighborList = getVisitables(w, stack.back());
    //if has neighbors
    if(neighborList.size() > 0) {
      //mark as visited
      w->SetNodeColor(stack.back(), Color::Red);
      //list neighbors
      //choose neighbor (rng)
      if(neighborList.size() == 1) {
      }
      else {
        switch(rands[i] % neighborList.size()) {

          //up
          case 0:
            stack.push_back(stack.back() + Point2D(0, 1));
          break;
          //right
          case 1:
            stack.push_back(stack.back() + Point2D(1, 0));
          break;
          //down
          case 2:
            stack.push_back(stack.back() + Point2D(0, -1));
            break;
          //left
          case 3:
            stack.push_back(stack.back() + Point2D(-1, 0));
            break;
        }
        i++;

      }

      //remove seperating wall
      //add neghbor to stack
    }

    //else remove top cell from stack backtrack
  }

  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  if(w->GetNorth(p)) {
    visitables.push_back(p.Up());
  }
  if(w->GetEast(p)) {
    visitables.push_back(p.Right());
  }
  if(w->GetSouth(p)) {
    visitables.push_back(p.Down());
  }
  if(w->GetWest(p)) {
    visitables.push_back(p.Left());
  }

  // todo: implement this

  return visitables;
}
