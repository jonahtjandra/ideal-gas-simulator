#include "gas_container.h"

#include <algorithm>

#include "particle.h"

#include "cinder/Rand.h"


using glm::vec2;

namespace idealgas {

GasContainer::GasContainer(const vec2& position_1, const vec2& position_2,
                           const vec2& velocity_1, const vec2& velocity_2,
                           const size_t size, double_t mass_1, double_t mass_2, double_t radius) {
  particles_.emplace_back(position_1, velocity_1, radius, mass_1, ci::Color("red"));
  particles_.emplace_back(position_2, velocity_2, radius, mass_2, ci::Color("red"));
  GasContainer::kSize = size;
}

GasContainer::GasContainer(const size_t size) {
  GasContainer::kSize = size;
}

void GasContainer::AddParticles(int number_of_particles, double speed,
                                double_t radius, double_t mass, const ci::Color& color) {
  for (int i = 0; i < number_of_particles; i++) {
    // making sure the speed of particles are the same
    float velocity_x = cinder::Rand::randFloat(-speed, speed);
    float velocity_y =
        std::sqrt((std::pow(speed, 2) - std::pow(velocity_x, 2)));
    particles_.emplace_back(Particle(vec2(kStartLocation , kStartLocation),
                            vec2(velocity_x, velocity_y), radius, mass, color));
  }
}

std::vector<Particle> GasContainer::GetParticles() const {
  return particles_;
}

void GasContainer::Display() {
  for (const Particle& particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(kMargin, kMargin), vec2(kSize, kSize)));
}

vec2 GasContainer::ComputeVelocity(Particle particle_1, Particle particle_2) const {
  // using formula from
  // https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional
  float mass_ratio = float (2 * particle_2.GetMass())/(particle_1.GetMass() + particle_2.GetMass());
  vec2 delta_distance = particle_1.GetPosition() - particle_2.GetPosition();
  float dot_product_velocity_distance = glm::dot(
      (particle_1.GetVelocity() - particle_2.GetVelocity()), delta_distance);
  vec2 velocity_after =
      particle_1.GetVelocity() -
          (mass_ratio * (delta_distance * vec2(dot_product_velocity_distance /
                             std::pow(glm::length(delta_distance), 2))));
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
  if (particle_2.GetPosition().y != particle_1.GetPosition().y
      && particle_2.GetPosition().x != particle_1.GetPosition().x) {
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
