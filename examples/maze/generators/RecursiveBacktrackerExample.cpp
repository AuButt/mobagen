#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <stack>

int i = 0;
bool started = false;
int rands[] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
std::stack<Point2D> stack;

bool RecursiveBacktrackerExample::Step(World* w) {
  Point2D prevPoint;
  auto sideOver2 = w->GetSize() / 2;
  //walls up
  //add top left to stack
  if(i == 0 && started == false) {
    stack.push_back(Point2D(-sideOver2, -sideOver2));
    started = true;
  }
  else if(i == 100) {
    i = 0;
  }

  //while stack empty
  if (!stack.empty()) {
    std::vector<Point2D> neighborList = getVisitables(w, stack.back());
    std::cout << stack.back().to_string() << "\t";;
    w->SetNodeColor(stack.back(), Color::Red);
    //if has neighbors
    if(neighborList.size() > 0) {
      //mark as visited

      prevPoint = stack.back();
      //list neighbors
      //choose neighbor (rng)
      //add neghbor to stack
      if(neighborList.size() == 1) {
        stack.push_back(neighborList.back());
      }
      else {
        stack.push_back(neighborList[rands[i] % neighborList.size()]);
        i++;
      }
      //remove seperating wall
      if(stack.back().Up() == prevPoint) {
        w->SetNorth(stack.back(), false);
      }
      else if(stack.back().Down() == prevPoint) {
        w->SetSouth(stack.back(), false);
      }
      else if(stack.back().Right() == prevPoint) {
        w->SetEast(stack.back(), false);
      }
      else if(stack.back().Left() == prevPoint) {
        w->SetWest(stack.back(), false);
      }

    }
    //else remove top cell from stack, backtrack
    else {
      //w->SetNodeColor(stack.back(), Color::Black);
      stack.pop_back();
      return true;
    }
    return true;
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
  if(p.Up().y > -sideOver2 -1 && w->GetNodeColor(p.Up()) != Color::Red) {
    visitables.push_back(p.Up());
    std::cout << "UP \t";
  }
  if(p.Right().x < sideOver2 +1 && w->GetNodeColor(p.Right()) != Color::Red) {
    visitables.push_back(p.Right());
    std::cout << "RIGHT \t";
  }
  if(p.Down().y < sideOver2 +1 && w->GetNodeColor(p.Down()) != Color::Red) {
    visitables.push_back(p.Down());
    std::cout << "DOWN \t";
  }
  if(p.Left().x > -sideOver2 -1 && w->GetNodeColor(p.Left()) != Color::Red) {
    visitables.push_back(p.Left());
    std::cout << "LEFT \t";
  }

  // todo: implement this
  std::cout << std::endl;
  return visitables;
}
