#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class Particle {
 public:
  /**
   * Constructor for Particle class.
   * @param position the position vector of the particle
   * @param velocity the velocity vector of the particle
   * @param radius the radius of the particle
   * @param color the color of the particle
   */
  Particle(vec2 position, vec2 velocity, int radius, ci::Color color);

  /**
   * getter for position_ of particle.
   * @return the position vector of the particle
   */
  vec2 GetPosition();

  /**
   * getter for velocity_ of particle.
   * @return the velocity vector of the particle
   */
  vec2 GetVelocity();

  /**
   * Setter for the position of particle.
   * @param position the position vector
   */
  void SetPosition(vec2 position);
  /**
   * Setter for the velocity of particle.
   * @param velocity the velocity vector
   */
  void SetVelocity(vec2 velocity);

  /**
   * Getter for radius_
   * @return the radius of the particle
   */
  int GetRadius();

  /**
   * Getter for color_
   * @return the color of the particle
   */
  ci::Color GetColor();

 private:
  vec2 position_;
  vec2 velocity_;
  int radius_;
  ci::Color color_;
};
}  // namespace idealgas