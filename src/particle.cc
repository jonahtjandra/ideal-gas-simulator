#include <particle.h>

using glm::vec2;

namespace idealgas {

Particle::Particle(vec2 position, vec2 velocity, double_t radius, double_t mass, ci::Color color) {
  Particle::mass_ = mass;
  Particle::position_ = position;
  Particle::velocity_ = velocity;
  Particle::radius_ = radius;
  Particle::color_ = color;
}

cinder::ColorT<float> Particle::GetColor() const {
  return Particle::color_;
}

int Particle::GetRadius() const {
  return Particle::radius_;
}

vec2 Particle::GetPosition() const {
  return Particle::position_;
}

vec2 Particle::GetVelocity() {
  return Particle::velocity_;
}

void Particle::SetPosition(vec2 position) {
  Particle::position_ = position;
}

void Particle::SetVelocity(vec2 velocity) {
  Particle::velocity_ = velocity;
}

int Particle::GetMass() {
  return mass_;
}

}  // namespace idealgas