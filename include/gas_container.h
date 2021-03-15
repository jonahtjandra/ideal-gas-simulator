#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  GasContainer(int number_of_particles_, int velocity, int radius, std::string color);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:
  std::vector<Particle> particles_;
  const int kSize = 700;
  void SortParticles(std::vector<Particle> &particles);
  vec2 Collide(Particle particle1, Particle particle2);
};

}  // namespace idealgas
