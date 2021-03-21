#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"


namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructor for GasContainer class. This class handles the physics and
   * dynamics of the simulation.
   * @param number_of_particles the number of particles simulated
   * @param speed the initial velocities of the particle
   * @param radius the radius of the particles
   * @param color the color of the particles
   * @param size the size of the particles
   */
  GasContainer(const size_t size);

  /**
   * Constructor for GasContainer class used for testing. This initializes the
   * particles manually so we can test them.
   * @param position_1 The position of the first particle
   * @param position_2 The position of the second particle
   * @param velocity_1 The velocity of the first particle
   * @param velocity_2 The velocity of the second particle
   * @param size The size of the particle
   * @param radius The radius of the particle
   */
  GasContainer(const vec2& position_1, const vec2& position_2, const vec2& velocity_1,
               const vec2& velocity_2, const size_t size, double_t mass_1, double_t mass_2, double_t radius);

  /**
   *
   */
  void AddParticles(int number_of_particles, double speed, double_t radius, double_t mass,
                    const ci::Color& color);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles based on a perfectly
   * elastic collision.
   */
  void AdvanceOneFrame();

  /**
   * Method used to return a vector of all particles currently being simulated.
   * @return vector of all particles currently being simulated
   */
  std::vector<Particle> GetParticles() const;

 private:
  //vector representation of particles in the simulator
  std::vector<Particle> particles_;
  //size of the container
  double_t kSize;
  //margin for drawing the container
  int kMargin = 150;
  //starting location of particles
  int kStartLocation = kMargin + 30;
  /**
   * Helper method used to return the velocities of particles at impact
   * @param particle_1 The first particle object
   * @param particle_2 The second particle object
   * @return the vec2 representation of particle 1's velocity
   */
  vec2 ComputeVelocity(Particle particle_1, Particle particle_2);

  /**
   * Helper method used to handle wall collisions.
   * @param particle the particle that is being handled for wall collisions
   */
  void ComputeCollisionWall(Particle& particle);

  /**
   * Helper method used to handle particle to particle collisions.
   * @param particle_1 The first particle object in the collision
   * @param particle_2 The second particle object in the collision
   */
  void ComputeCollisionParticle(Particle& particle_1, Particle& particle_2);
};

}  // namespace idealgas
