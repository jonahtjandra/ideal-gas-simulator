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

  GasContainer(int number_of_particles_, int velocity, int radius, ci::Color color, const int size);

  GasContainer(vec2 particle_1, vec2 particle_2, vec2 velocity_1, vec2 velocity_2, const int size);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  std::vector<Particle> GetParticles();

 private:
  std::vector<Particle> particles_;
  int kSize;
  vec2 Collide(Particle particle1, Particle particle2);
};

}  // namespace idealgas
