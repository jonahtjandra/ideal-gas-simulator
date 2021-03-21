#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"


namespace idealgas {

class SpeedHistogram {
 public:
  SpeedHistogram(std::vector<Particle> particles, const size_t start_point, const ci::Color color);
  /**
   * Displays the histogram and the bins.
   */
  void Display() const;
  /**
   * Updates the histogram
   */
  void AdvanceOneFrame();

 private:
  const double max_speed_ = 5;
  std::vector<float> bin_height_;
  const int kBins = 10;
  const size_t kMargin = 130;
  size_t kSize = 100;
  size_t kStartPoint;
  ci::Color kColor;
  std::vector<Particle> particles_;
  const size_t kTextSpacing = 10;
};

} // namespace idealgas
