#include <catch2/catch.hpp>
#include <particle.h>
#include <gas_container.h>

using idealgas::GasContainer;
using glm::vec2;

//https://www.tutorialspoint.com/floating-point-comparison-in-cplusplus
bool compare_float(float x, float y, float epsilon = 0.0001f){
  if(fabs(x - y) < epsilon)
    return true; //they are same
  return false; //they are not same
}

TEST_CASE("Colliding") {

  SECTION("Colliding with each other particle 1") {
    GasContainer container = GasContainer(vec2(20,20),
                                          vec2(21.4, 21.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(glm::length(container.GetParticles().at(1).GetVelocity()), 0.1f));
    container.GetParticles().empty();
  }

  SECTION("Colliding with each other particle 2") {
    GasContainer container = GasContainer(vec2(20,20),
                                          vec2(21.4, 21.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(glm::length(container.GetParticles().at(1).GetVelocity()), 0.1f));
    container.GetParticles().empty();
  }

  SECTION("Colliding with right vertical wall") {

    GasContainer container = GasContainer(vec2(39.1,20),
                                          vec2(21.4, 21.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(0).GetVelocity().x, -0.1f));
  }

  SECTION("Colliding with bottom horizontal wall") {

    GasContainer container = GasContainer(vec2(39.1,20),
                                          vec2(21.4, 39.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0.1), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(1).GetVelocity().y, -0.1f));
  }

  SECTION("Colliding with left vertical wall") {

    GasContainer container = GasContainer(vec2(5.8,20),
                                          vec2(21.4, 39.4),
                                          vec2(-0.2, 0),
                                          vec2(-0.1, 0.1), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(0).GetVelocity().x, 0.2f));
  }

  SECTION("Colliding with top horizontal wall") {

    GasContainer container = GasContainer(vec2(5.8,20),
                                          vec2(21.4, 5.4),
                                          vec2(-0.2, 0),
                                          vec2(-0.1, 0.4), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(1).GetVelocity().y, -0.4f));
  }

  SECTION("Overlapping but moving in the same direction") {

    GasContainer container = GasContainer(vec2(7,7),
                                          vec2(7, 7),
                                          vec2(-0.1, 0.1),
                                          vec2(-0.1, 0.1), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(1).GetVelocity().y, 0.1f));
  }
}
TEST_CASE("Edge cases") {

}

