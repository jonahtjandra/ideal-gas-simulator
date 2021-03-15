#include "gas_container.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

GasContainer::GasContainer(int num_of_particles, int velocity, int radius, std::string color) {
  for (int i = 0; i < num_of_particles; i++) {
    float velocity_x = ((float) std::rand()) * velocity / (float) RAND_MAX;
    float velocity_y = std::sqrt((std::pow(velocity, 2) - std::pow(velocity_x, 2)));
    particles_.push_back(Particle(vec2(150,150), vec2(velocity_x,velocity_y), radius, color));
  }
}

bool CompareParticles(Particle particle1, Particle particle2) {
  return (particle1.GetPosition().x < particle2.GetPosition().x);
}

void GasContainer::SortParticles(std::vector<Particle> &particles) {
  std::sort(particles.begin(), particles.end(), CompareParticles);
}

void GasContainer::Display() {
  ci::gl::color(ci::Color("blue"));
  ci::gl::drawSolidCircle(vec2(696,696), 5);
  for (Particle &particle : particles_) {
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(50, 50), vec2(kSize, kSize)));
}

vec2 GasContainer::Collide (Particle particle1, Particle particle2) {
  vec2 distance = particle1.GetPosition() - particle2.GetPosition();
  vec2 velocity = (particle1.GetVelocity() -
      (static_cast<float>(glm::dot(particle1.GetVelocity() - particle2.GetVelocity(),distance)
           /std::pow((glm::length(distance)), 2)) *
(distance)));
  return velocity;
}

void GasContainer::AdvanceOneFrame() {
  for (Particle &particle : particles_) {
    if (particle.GetVelocity().x > 0.0 || particle.GetVelocity().y > 0.0) {
      //colliding with horizontal wall
      if (700 - particle.GetPosition().y <= particle.GetRadius()) {
        particle.SetVelocity(vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
      }
      //colliding with vertical wall
      if (700 - particle.GetPosition().x <= particle.GetRadius()) {
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
    for (Particle &particle2 : particles_)
    if (glm::dot((particle.GetVelocity()-particle2.GetVelocity()), (particle.GetPosition()-particle2.GetPosition())) < 0) {
      if (glm::distance(particle.GetPosition(), particle2.GetPosition())
          <= particle.GetRadius()) {
        std::cout << particle2.GetVelocity();
        std::cout << " before || after ";
        std::cout << GasContainer::Collide(particle2, particle);
        std::cout << " |||| ";
        std::cout << particle.GetVelocity();
        std::cout << " before || after ";
        std::cout << GasContainer::Collide(particle,particle2);
        particle.SetVelocity(GasContainer::Collide(particle,particle2));
        particle2.SetVelocity(GasContainer::Collide(particle2, particle));
      }
    }
    particle.SetPosition(particle.GetPosition()+particle.GetVelocity());
  }
}

}  // namespace idealgas
