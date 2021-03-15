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
  SECTION("Colliding with each other particle 2") {
    GasContainer container = GasContainer(vec2(20,20),
                                          vec2(21.4, 21.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(glm::length(container.GetParticles().at(1).GetVelocity()), 0.1f));
    container.GetParticles().empty();
  }

  SECTION("Colliding with a vertical wall") {

    GasContainer container = GasContainer(vec2(39.1,20),
                                          vec2(21.4, 21.4),
                                          vec2(0.1, 0),
                                          vec2(-0.1, 0), 40, 1);
    container.AdvanceOneFrame();
    REQUIRE(compare_float(container.GetParticles().at(0).GetVelocity().x, -0.1f));
  }

}


