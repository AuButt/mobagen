#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood


  for(const Boid* b: neighborhood) {
    int massCount = 0;
    Vector2f sepVec = {boid->getPosition().x - b->getPosition().x, boid->getPosition().y - b->getPosition().y};
    //calc distance between boids
    float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);

    if(dist < boid->getDetectionRadius()) {
      massCount++;
      //averageVelocity = {averageVelocity.x + b->getPosition().x, averageVelocity.y + b->getPosition().y};
    }
    if(massCount != 0) {
      averageVelocity = averageVelocity/massCount;

      //Vector2f sepVec = centerOfMass - boid->getPosition();

    }
  }

  averageVelocity = Vector2f::normalized(averageVelocity);
  return averageVelocity;
}