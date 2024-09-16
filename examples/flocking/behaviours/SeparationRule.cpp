#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  //Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

  Vector2f result = {0,0};
  for(const Boid* b: neighborhood) {
    Vector2f sepVec = {boid->getPosition().x - b->getPosition().x, boid->getPosition().y - b->getPosition().y};
    // calc dist between boids
    float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);
    // if inside sep radius, build force
    if(dist < desiredMinimalDistance && dist > 0.01f) {

      //normalize separation vector
      sepVec = {sepVec.x / dist, sepVec.y / dist};
      float force = 1 / dist;
      result = {result.x + sepVec.x*force, result.y + sepVec.y*force};
    }
  }
  result = Vector2f::normalized(result);

  return result;

 // separatingForce = Vector2f::normalized(separatingForce);

  //return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}

/*
---Seperation
get force of neighbor radius
inner neighbor pos - boid pos == direction force
everything normalized
(transforming into unit vector)
divide by magnitude

Vec2 SeperationForce(const Boid& boid, const std::vector<Boid> neighbors, float seperationRadius)
{
Vec2 result = {.x:0,.y:0};
  for(const Boid b: neighbors)
  {
    //remove itself
    if(boid.position.x == b.position.x && boid.position.y == b.position.y)
    {
      continue;
    }
    Vec2 sepVec = {boid.position.x - b.position.x, boid.position.y - b.position.y};
    //calc distance between boids
    float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);
    // if its inside sep radius accumulate force
    if(dist < seperationRadius && dist > 0.01) {
    //normalize
    //can use seperation radius also
      sepVec = {sepVec.x/dist, sepVec.y/dist};
      float force = 1/dist;
      result = {result.x + sepVec.x*force, result.y + sepVec.y*force}
    }
  }
  return result;
}

If force is too strong, clamp

*/
