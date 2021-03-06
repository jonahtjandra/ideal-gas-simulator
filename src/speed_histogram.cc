#include "speed_histogram.h"
#include "cinder/svg/Svg.h"

namespace idealgas {

SpeedHistogram::SpeedHistogram(std::vector<Particle> particles, const size_t start_point, const ci::Color& color) {
  particles_ = particles;
  kStartPoint = start_point;
  kColor = color;

}

std::vector<Particle> SpeedHistogram::GetParticle() const {
  return particles_;
}

std::vector<float> SpeedHistogram::GetBinHeight() const {
  return bin_height_;
}

void SpeedHistogram::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered("Number of Particles",vec2(kStartPoint, kMargin - kSize - kTextSpacing),ci::Color("white"));
  ci::gl::drawStringCentered("Speed",vec2(kStartPoint + kSize/2, kMargin + 5),ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kStartPoint, kMargin), vec2(kStartPoint + kSize, kMargin)));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kStartPoint, kMargin), vec2(kStartPoint, kMargin - kSize)));
  for (int i = 0; i < kBins; i++) {
    ci::gl::color(ci::Color(kColor));
    ci::gl::drawSolidRect(ci::Rectf(vec2(kStartPoint + (kSize * i/kBins), kMargin), vec2(kStartPoint + (kSize * i/kBins) + (kSize/kBins), ((1 - bin_height_.at(i)) * kMargin))));
  }
}

void SpeedHistogram::AdvanceOneFrame() {
  bin_height_.clear();
  double bin_speed = max_speed_ / kBins;
  for (int i = 0; i < kBins; i++) {
    int count = 0;
    for (Particle particle : particles_) {
      if (glm::length(particle.GetVelocity()) >= (bin_speed * i) &&
          glm::length(particle.GetVelocity()) < (bin_speed * (i + 1))) {
        count++;
      }
      if (glm::length(particle.GetVelocity()) > max_speed_ && i == kBins - 1) {
        count++;
      }
    }
    bin_height_.emplace_back(static_cast<float>(count)/static_cast<float>(particles_.size()));
  }
}
} //namespace idealgas
