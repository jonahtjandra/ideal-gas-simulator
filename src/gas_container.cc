#include "gas_container.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

GasContainer::GasContainer(vec2 particle_1, vec2 particle_2, vec2 velocity_1, vec2 velocity_2, const int size) {
  particles_.push_back(Particle(particle_1, velocity_1, 1, ci::Color("red")));
  particles_.push_back(Particle(particle_2, velocity_2, 1, ci::Color("red")));
  GasContainer::kSize = size;
}

GasContainer::GasContainer(int num_of_particles, int velocity, int radius, ci::Color color, const int size) {
  GasContainer::kSize = size;
  for (int i = 0; i < num_of_particles; i++) {
    float velocity_x = ((double) std::rand()) * velocity / (double) RAND_MAX;
    float velocity_y = std::sqrt((std::pow(velocity, 2) - std::pow(velocity_x, 2)));
    particles_.push_back(Particle(vec2(150,150), vec2(velocity_x,velocity_y), radius, color));
  }
}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::Display() {
  for (Particle &particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(50, 50), vec2(kSize, kSize)));
}

vec2 GasContainer::Collide (Particle particle1, Particle particle2) {
  vec2 distance = particle1.GetPosition() - particle2.GetPosition();
  std::cout << "vel2 " << particle1.GetVelocity();
  float dot_product = glm::dot((particle1.GetVelocity() - particle2.GetVelocity()),distance);
  std::cout << "dot Product:  " << dot_product;
  vec2 vec = distance * vec2(dot_product / std::pow(glm::length(distance), 2));
  vec2 velocity = particle1.GetVelocity() - vec;
  std::cout << velocity;
  return velocity;
}

void GasContainer::AdvanceOneFrame() {
  for (Particle& particle : particles_) {
    if (particle.GetVelocity().x > 0.0 || particle.GetVelocity().y > 0.0) {
      //colliding with horizontal wall
      if (kSize - particle.GetPosition().y <= particle.GetRadius()) {
        particle.SetVelocity(vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
      }
      //colliding with vertical wall
      if (kSize - particle.GetPosition().x <= particle.GetRadius()) {
        particle.SetVelocity(vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
      }
    }
    if (particle.GetVelocity().x < 0.0 || particle.GetVelocity().y < 0.0) {
      if (particle.GetPosition().y - 50 <= particle.GetRadius()) {
        particle.SetVelocity(vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
      }
      //colliding with vertical wall
      if (particle.GetPosition().x - 50 <= particle.GetRadius()) {
        particle.SetVelocity(vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
      }
    }
    //colliding with each other
    for (Particle& particle2 : particles_) {
      if (particle2.GetPosition() != particle.GetPosition()) {
        if (glm::distance(particle.GetPosition(), particle2.GetPosition()) <= 2 * particle.GetRadius()) {
          if (glm::dot(particle.GetVelocity()-particle2.GetVelocity(), (particle.GetPosition()-particle2.GetPosition())) < 0) {
            vec2 velocity1 = GasContainer::Collide(particle,particle2);
            vec2 velocity2 = GasContainer::Collide(particle2,particle);
            particle.SetVelocity(velocity1);
            particle2.SetVelocity(velocity2);
          }
        }
      }
    }
    std::cout << particle.GetVelocity();
    particle.SetPosition(particle.GetPosition()+particle.GetVelocity());
  }
}
}  // namespace idealgas
