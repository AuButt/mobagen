#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

#include <iostream>

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();;


  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood


  Vector2f mass = Vector2f::zero();
  int massCount = 0;
  // find center of mass
  for(const Boid* b: neighborhood) {
    Vector2f sepVec = {boid->getPosition().x - b->getPosition().x, boid->getPosition().y - b->getPosition().y};
    //calc distance between boids
    float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);

    if(dist < boid->getDetectionRadius()) {
      massCount++;
      mass = mass + Vector2f(b->getPosition().x, b->getPosition().y);
    }
  }
  if(massCount != 0) {
    Vector2f centerOfMass = mass/massCount;
    Vector2f sepVec = centerOfMass - boid->getPosition();

    cohesionForce = sepVec;
  }

  /*


  cohesionForce = {cohesionForce.x + sepVec.x*force, cohesionForce.y + sepVec.y*force};
*/

  /*
  Vector2f sepVec = {boid->getPosition().x - centerOfMass.x, boid->getPosition().y - centerOfMass.y};
  float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);


  float force = 1/dist;
  cohesionForce = {cohesionForce.x + sepVec.x*force, cohesionForce.y + sepVec.y*force};
 */


  return cohesionForce;
}
