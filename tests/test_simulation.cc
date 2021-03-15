#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Colliding with each other") {
  GasContainer container = GasContainer(vec2(20,20),
                                        vec2(21.4, 21.4),
                                        vec2(0.1, 0),
                                        vec2(-0.1, 0), 40);
  container.AdvanceOneFrame();
  REQUIRE(container.GetParticles().at(1).GetVelocity().y == (float)0.1);
}


