#include <particle.h>

using glm::vec2;

namespace idealgas {

Particle::Particle(vec2 position, vec2 velocity, size_t radius, ci::Color color) {
  Particle::position_ = position;
  Particle::velocity_ = velocity;
  Particle::radius_ = radius;
  Particle::color_ = color;
}

cinder::ColorT<float> Particle::GetColor() {
  return Particle::color_;
}

int Particle::GetRadius() {
  return Particle::radius_;
}

vec2 Particle::GetPosition() {
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

}  // namespace idealgas