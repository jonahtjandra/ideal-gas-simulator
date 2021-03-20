#include <gas_container.h>
#include <particle.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::GasContainer;

// https://www.tutorialspoint.com/floating-point-comparison-in-cplusplus
bool compare_float(float x, float y, float epsilon = 0.0001f) {
  if (fabs(x - y) < epsilon) {
    return true;  // they are same
  }
  return false;  // they are not same
}

TEST_CASE("Constructor") {
  SECTION("Test GetParticles") {
    GasContainer container = GasContainer(600);
    container.AddParticles(88, 1, 1, 1, ci::Color("red"));
    REQUIRE(container.GetParticles().size() == 88);
  }
}

TEST_CASE("Colliding") {
  SECTION("Colliding horizontally with each other at the same speed") {
    GasContainer container = GasContainer(vec2(20, 20), vec2(21.4, 21.4),
                                          vec2(0.1, 0), vec2(-0.1, 0), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE((compare_float((container.GetParticles().at(0).GetVelocity().y),
                           -0.1f) &&
             (compare_float((container.GetParticles().at(1).GetVelocity().y),
                            0.1f))));
  }

  SECTION("Colliding horizontally with each other at different speed") {
    GasContainer container = GasContainer(vec2(20, 20), vec2(21.4, 21.4),
                                          vec2(0.18, 0), vec2(-0.12, 0), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE((
        compare_float(glm::length(container.GetParticles().at(0).GetVelocity()),
                      0.15297f) &&
        (compare_float(
            glm::length(container.GetParticles().at(1).GetVelocity()),
            0.15297f))));
  }

  SECTION("Colliding vertically with each other at the same speed") {
    GasContainer container = GasContainer(vec2(20, 20), vec2(21.4, 21.4),
                                          vec2(0, 0.1), vec2(0, -0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE((compare_float((container.GetParticles().at(0).GetVelocity().x),
                           -0.1f) &&
             (compare_float((container.GetParticles().at(1).GetVelocity().x),
                            0.1f))));
  }

  SECTION("Colliding vertically with each other at different speed") {
    GasContainer container = GasContainer(vec2(20, 20), vec2(21.4, 21.4),
                                          vec2(0, 0.21), vec2(0, -0.03), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE((
        compare_float(glm::length(container.GetParticles().at(0).GetVelocity()),
                      0.15f) &&
        (compare_float(
            glm::length(container.GetParticles().at(1).GetVelocity()),
            0.15f))));
  }

  SECTION("Colliding with right vertical wall") {
    GasContainer container = GasContainer(vec2(39.1, 20), vec2(21.4, 21.4),
                                          vec2(0.1, 0), vec2(-0.1, 0), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(0).GetVelocity().x, -0.1f));
  }

  SECTION("Colliding with bottom horizontal wall") {
    GasContainer container = GasContainer(vec2(39.1, 20), vec2(21.4, 39.4),
                                          vec2(0.1, 0), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(1).GetVelocity().y, -0.1f));
  }

  SECTION("Colliding with left vertical wall") {
    GasContainer container = GasContainer(
        vec2(5.8, 20), vec2(21.4, 39.4), vec2(-0.2, 0), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(0).GetVelocity().x, 0.2f));
  }

  SECTION("Colliding with top horizontal wall") {
    GasContainer container = GasContainer(
        vec2(5.8, 20), vec2(21.4, 5.4), vec2(-0.2, 0), vec2(-0.1, 0.4), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(1).GetVelocity().y, -0.4f));
  }

  SECTION("Overlapping but moving in the same direction") {
    GasContainer container = GasContainer(
        vec2(7, 7), vec2(7, 7), vec2(-0.1, 0.1), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(1).GetVelocity().y, 0.1f));
  }
  SECTION("Particle colliding with stationary particle") {
    GasContainer container =
        GasContainer(vec2(7, 7), vec2(8, 8), vec2(1, 0), vec2(0, 0), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(1).GetVelocity().y, 0.5f));
  }
  SECTION("Particle colliding with different mass") {
    GasContainer container = GasContainer(vec2(20, 20), vec2(21.4, 21.4),
                                          vec2(0.18, 0), vec2(-0.12, 0), 40, 2, 3, 1);
    container.AdvanceOneFrame();
    std::cout << container.GetParticles().at(0).GetVelocity();
    REQUIRE((
                compare_float(glm::length(container.GetParticles().at(0).GetVelocity()),
                              0.1529706f) &&
                (compare_float(
                    glm::length(container.GetParticles().at(1).GetVelocity()),
                    0.12f))));
  }
}
TEST_CASE("Edge cases for collisions") {
  SECTION("Particle overlapping but moving in the same direction") {
    GasContainer container = GasContainer(
        vec2(7, 7), vec2(7, 7), vec2(-0.1, 0.1), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(1).GetVelocity().y, 0.1f));
  }
  SECTION("Particle touching the wall but moving away") {
    GasContainer container = GasContainer(
        vec2(5, 7), vec2(20, 20), vec2(0.1, 0.1), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(0).GetVelocity().x, 0.1f));
  }
  SECTION(
      "Particle touching the horizontal wall but zero x-component velocity") {
    GasContainer container = GasContainer(vec2(5.8, 7), vec2(20, 20),
                                          vec2(0, 0.1), vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(0).GetVelocity().x, 0.0f));
  }
  SECTION("Particle touching the vertical wall but zero y-component velocity") {
    GasContainer container = GasContainer(vec2(9, 5), vec2(20, 20), vec2(0, 0),
                                          vec2(-0.1, 0.1), 40, 1, 1, 1);
    container.AdvanceOneFrame();
    REQUIRE(
        compare_float(container.GetParticles().at(0).GetVelocity().y, 0.0f));
  }
}
