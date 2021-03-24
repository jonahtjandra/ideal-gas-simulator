#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"


namespace idealgas {

class SpeedHistogram {
 public:
  /**
   * Constructor for speed histogram
   * @param particles the particles that is plotted
   * @param start_point the starting point to draw the diagram
   * @param color the color of the histogram
   */
  SpeedHistogram(std::vector<Particle> particles, const size_t start_point, const ci::Color& color);
  /**
   * Displays the histogram and the bins.
   */
  void Display() const;
  /**
   * Updates the histogram
   */
  void AdvanceOneFrame();

  /**
   * Getter method for particles used for testing
   * @return a vector of the particles
   */
  std::vector<Particle> GetParticle() const;

  /**
   * Getter method for bin height used for testing
   * @return a vector of bin heights
   */
  std::vector<float> GetBinHeight() const;

 private:
  //domain of the histogram
  const double max_speed_ = 5;
  std::vector<float> bin_height_;
  const int kBins = 10;
  //spacing between histograms
  const size_t kMargin = 130;
  //size of histograms
  size_t kSize = 100;
  size_t kStartPoint;
  ci::Color kColor;
  //particles being plotted
  std::vector<Particle> particles_;
  const size_t kTextSpacing = 10;
};

} // namespace idealgas
