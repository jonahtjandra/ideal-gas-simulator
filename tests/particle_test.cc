#include <particle.h>

#include <catch2/catch.hpp>

using glm::vec2;

TEST_CASE("Constructing new particles") {
  idealgas::Particle particle =
      idealgas::Particle(vec2(10, 10), vec2(1, 1), 10, ci::Color("red"));
  SECTION("Test GetPosition") {
    REQUIRE(
        ((particle.GetPosition().y == 10) && (particle.GetPosition().x == 10)));
  }
  SECTION("Test GetVelocity") {
    REQUIRE(
        ((particle.GetVelocity().y == 1) && (particle.GetVelocity().x == 1)));
  }
  SECTION("Test GetRadius") {
    REQUIRE(particle.GetRadius() == 10);
  }
  SECTION("Test GetColor") {
    REQUIRE(particle.GetColor() == ci::Color("red"));
  }
  SECTION("Test SetVelocity") {
    particle.SetVelocity(vec2(3, 3));
    REQUIRE(
        ((particle.GetVelocity().y == 3) && (particle.GetVelocity().x == 3)));
  }
  SECTION("Test SetPosition") {
    particle.SetPosition(vec2(100, 100));
    REQUIRE(((particle.GetPosition().y == 100) &&
             (particle.GetPosition().x == 100)));
  }
}
