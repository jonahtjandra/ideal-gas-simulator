#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class Particle {
 public:
  Particle(vec2 position, vec2 velocity, int radius, ci::Color color);
  vec2 GetPosition();
  vec2 GetVelocity();
  void SetPosition(vec2 position);
  void SetVelocity(vec2 velocity);
  int GetRadius();
  ci::Color GetColor();

 private:
  vec2 position_;
  vec2 velocity_;
  int radius_;
  ci::Color color_;
};
}  // namespace idealgas