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
  SortParticles(particles_);
  for (Particle &particle : particles_) {
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(50, 50), vec2(kSize, kSize)));
}

vec2 GasContainer::Collide (Particle particle1, Particle particle2) {
  vec2 velocity = (particle1.GetVelocity() -
      (static_cast<float>(glm::dot(particle1.GetVelocity() - particle2.GetVelocity(),
                                               (particle1.GetPosition() - particle2.GetPosition()))
           /std::pow((glm::length(particle1.GetPosition() - particle2.GetPosition())), 2)) *
(particle1.GetPosition() - particle2.GetPosition())));
  return velocity;
}

void GasContainer::AdvanceOneFrame() {
  int count = 1;
  std::vector<Particle>& particles_ref = particles_;
  for (Particle &particle : particles_) {
    //colliding with horizontal wall
    if (particle.GetPosition().y <= 50 || particle.GetPosition().y >= 700) {
      particle.SetVelocity(vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
    }
    //colliding with vertical wall
    if (particle.GetPosition().x <= 50 || particle.GetPosition().x >= 700) {
      particle.SetVelocity(-vec2(particle.GetVelocity().x, particle.GetVelocity().y));
    }
    //colliding with each other
    if (glm::dot((particle.GetVelocity()-particles_.at(count).GetVelocity()), (particle.GetPosition()-particles_.at(count).GetPosition())) < 0) {
      if (glm::distance(particle.GetPosition(), particles_.at(count).GetPosition())
          <= particle.GetRadius()) {
        std::cout << particles_ref.at(count).GetVelocity();
        std::cout << " before || after ";
        std::cout << GasContainer::Collide(particles_.at(count), particle);
        std::cout << " |||| ";
        std::cout << particle.GetVelocity();
        std::cout << " before || after ";
        std::cout << GasContainer::Collide(particle,particles_.at(count));
        particle.SetVelocity(GasContainer::Collide(particle,particles_.at(count)));
        particles_ref.at(count).SetVelocity(GasContainer::Collide(particles_.at(count), particle));
      }
    }
    particle.SetPosition(particle.GetPosition()+particle.GetVelocity());
    if (count < particles_.size() - 1) {
      count++;
    }
  }
}

}  // namespace idealgas
