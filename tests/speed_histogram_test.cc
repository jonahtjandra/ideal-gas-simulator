#include <speed_histogram.h>

#include <catch2/catch.hpp>

using idealgas::SpeedHistogram;


// https://www.tutorialspoint.com/floating-point-comparison-in-cplusplus
bool compare(float x, float y, float epsilon = 0.0001f) {
  if (fabs(x - y) < epsilon) {
    return true;  // they are same
  }
  return false;  // they are not same
}

TEST_CASE("SpeedHistogram Constructor") {
  SECTION("Test SpeedHistogram particle initialization") {
    std::vector<idealgas::Particle> particles;
    for (int i = 0; i <= 10; i++) {
      particles.emplace_back(vec2(i,i), vec2(i,i), 2, 1, ci::Color("red"));
    }
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    REQUIRE(histogram.GetParticle().size() == 11);
  }
}

TEST_CASE("SpeedHistogram bin height") {
  SECTION("Test number of bins correctly configured") {
    std::vector<idealgas::Particle> particles;
    for (int i = 0; i <= 9; i++) {
      particles.emplace_back(vec2(i,i), vec2(i,i), 2, 1, ci::Color("red"));
    }
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    REQUIRE(histogram.GetBinHeight().size() == 10);
  }
  SECTION("Test bin height when particle is resting at the first bin") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,2), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    //because one of the particle is resting the first bin will have one particle yielding a 0.33333f
    REQUIRE(compare(histogram.GetBinHeight().at(0), 0.33333f));
  }
  SECTION("Test bin height at the second bin") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,1.5), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    REQUIRE(compare(histogram.GetBinHeight().at(1), 0));
  }
  SECTION("Test bin height at the third bin") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,0.8), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,1), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();

    REQUIRE(compare(histogram.GetBinHeight().at(2), 0.66667f));
  }
  SECTION("Test bin height when adding stationary particle") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,2), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(0,0), vec2(0,0), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    REQUIRE(compare(histogram.GetBinHeight().at(0), 0.5f));
  }
  SECTION("Test bin height at max speed") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,2), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(20,20), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(0,0), vec2(3.9,3), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    REQUIRE(compare(histogram.GetBinHeight().at(9), 0.2f));
  }
}
TEST_CASE("Edge Cases") {
  SECTION("Test bin height at over upper register") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1,1), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(30,20), vec2(0,0), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(40,40), vec2(1,2), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(20,20), vec2(5,5), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(0,0), vec2(10,10), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    //values higher than max register will be placed at the last bin
    REQUIRE(compare(histogram.GetBinHeight().at(9), 0.4f));
  }
  SECTION("Test bin height at the border between two bins") {
    std::vector<idealgas::Particle> particles;
    particles.emplace_back(vec2(0,0), vec2(1.414,1.414), 2, 1, ci::Color("red"));
    particles.emplace_back(vec2(0,0), vec2(1.42,1.42), 2, 1, ci::Color("red"));
    SpeedHistogram histogram = SpeedHistogram(particles, 3, ci::Color("red"));
    histogram.AdvanceOneFrame();
    //upper bin boundary is exclusive while lower boundary is inclusive
    REQUIRE(((compare(histogram.GetBinHeight().at(3), 0.5f)) && (compare(histogram.GetBinHeight().at(4), 0.5f))));
  }
}
