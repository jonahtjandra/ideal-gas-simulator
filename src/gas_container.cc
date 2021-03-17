#include "gas_container.h"

#include <algorithm>

#include "particle.h"

using glm::vec2;

namespace idealgas {

GasContainer::GasContainer(const vec2& position_1, const vec2& position_2,
                           const vec2& velocity_1, const vec2& velocity_2,
                           const size_t size, size_t radius) {
  particles_.emplace_back(position_1, velocity_1, radius, ci::Color("red"));
  particles_.emplace_back(position_2, velocity_2, radius, ci::Color("red"));
  GasContainer::kSize = size;
}

GasContainer::GasContainer(int number_of_particles, int speed, size_t radius,
                           const ci::Color& color, const size_t size) {
  GasContainer::kSize = size;
  for (int i = 0; i < number_of_particles; i++) {
    // making sure the speed of particles are the same
    float velocity_x = (static_cast<float>(std::rand())) * speed /
                       static_cast<float>(RAND_MAX);
    float velocity_y =
        std::sqrt((std::pow(speed, 2) - std::pow(velocity_x, 2)));
    particles_.emplace_back(vec2(kStartLocation, kStartLocation),
                            vec2(velocity_x, velocity_y), radius, color);
  }
}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::Display() {
  for (Particle& particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(kMargin, kMargin), vec2(kSize, kSize)));
}

vec2 GasContainer::ComputeVelocity(Particle particle_1, Particle particle_2) {
  // using formula from
  // https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional
  vec2 delta_distance = particle_1.GetPosition() - particle_2.GetPosition();
  float dot_product_velocity_distance = glm::dot(
      (particle_1.GetVelocity() - particle_2.GetVelocity()), delta_distance);
  vec2 velocity_after =
      particle_1.GetVelocity() -
      (delta_distance * vec2(dot_product_velocity_distance /
                             std::pow(glm::length(delta_distance), 2)));
  return velocity_after;
}

void GasContainer::ComputeCollisionWall(Particle& particle) {
  // checking if particle's velocity vector is heading towards the wall
  if (particle.GetVelocity().x > 0.0 || particle.GetVelocity().y > 0.0) {
    // colliding with bottom wall
    if (std::abs(kSize - particle.GetPosition().y) <= particle.GetRadius()) {
      particle.SetVelocity(
          vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
    }
    // colliding with right vertical wall
    if (std::abs(kSize - particle.GetPosition().x) <= particle.GetRadius()) {
      particle.SetVelocity(
          vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
    }
  }
  // checking if particle's velocity vector is heading towards the wall
  if (particle.GetVelocity().x < 0.0 || particle.GetVelocity().y < 0.0) {
    // colliding with top wall
    if (std::abs(particle.GetPosition().y - kMargin) <= particle.GetRadius()) {
      particle.SetVelocity(
          vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
    }
    // colliding with left vertical wall
    if (std::abs(particle.GetPosition().x - kMargin) <= particle.GetRadius()) {
      particle.SetVelocity(
          vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
    }
  }
}

void GasContainer::ComputeCollisionParticle(Particle& particle_1,
                                            Particle& particle_2) {
  // making sure particle_1 is different with particle_2
  if (&particle_2 != &particle_1) {
    // making sure the distance is less than both the particle's radius
    // (collision)
    if (glm::distance(particle_1.GetPosition(), particle_2.GetPosition()) <=
        particle_2.GetRadius() + particle_1.GetRadius()) {
      // making sure they are moving in opposite direction
      if (glm::dot(particle_1.GetVelocity() - particle_2.GetVelocity(),
                   (particle_1.GetPosition() - particle_2.GetPosition())) < 0) {
        vec2 velocity_1 = GasContainer::ComputeVelocity(particle_1, particle_2);
        vec2 velocity_2 = GasContainer::ComputeVelocity(particle_2, particle_1);
        particle_1.SetVelocity(velocity_1);
        particle_2.SetVelocity(velocity_2);
      }
    }
  }
}

void GasContainer::AdvanceOneFrame() {
  for (Particle& particle_1 : particles_) {
    // handling colliding with wall
    ComputeCollisionWall(particle_1);
    // handling colliding with each other
    for (Particle& particle_2 : particles_) {
      ComputeCollisionParticle(particle_1, particle_2);
    }
    particle_1.SetPosition(particle_1.GetPosition() + particle_1.GetVelocity());
  }
}
}  // namespace idealgas
