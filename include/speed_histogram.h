#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"


namespace idealgas {

class SpeedHistogram {
 public:
  SpeedHistogram(std::vector<Particle> particles, const size_t size, const ci::Color color, const double max_speed);
  /**
   * Displays the histogram and the bins.
   */
  void Display();
  /**
   * Updates the histogram
   */
  void AdvanceOneFrame();

  void UpdateParticles(std::vector<Particle> particles);

 private:
  double max_speed_;
  std::vector<float> bin_height_;
  const int kBins = 15;
  const size_t kMargin = 130;
  size_t kSize;
  ci::Color kColor;
  std::vector<Particle> particles_;
};

} // namespace idealgas
