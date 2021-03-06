#include "gas_simulation_app.h"

#include <iostream>

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  container_.AddParticles(30, 3, 4, 1, ci::Color(particle_color_1));
  container_.AddParticles(30, 2, 6, 3, ci::Color(particle_color_2));
  container_.AddParticles(30, 1, 8, 5, ci::Color(particle_color_3));
}

void IdealGasApp::CreateHistogram(const GasContainer container) {
  std::vector<Particle> particle_1;
  std::vector<Particle> particle_2;
  std::vector<Particle> particle_3;
  for (const Particle& particle : container.GetParticles()) {
    if (particle.GetColor() == particle_color_1) {
      particle_1.push_back(particle);
    } else if (particle.GetColor() == particle_color_2) {
      particle_2.push_back(particle);
    } else if (particle.GetColor() == particle_color_3) {
      particle_3.push_back(particle);
    }
  }
  histograms_.emplace_back(particle_3, kHistogramStartingPoint, particle_color_3);
  histograms_.emplace_back(particle_2,
                           kHistogramStartingPoint + kHistogramSpacing, particle_color_2);
  histograms_.emplace_back(particle_1,
      kHistogramStartingPoint + kHistogramSpacing + kHistogramSpacing, particle_color_1);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
  for (SpeedHistogram histogram : histograms_) {
    histogram.Display();
  }
}

void IdealGasApp::keyDown(cinder::app::KeyEvent event) {
  if (event.getChar() == 'w') {
    // increase speed
    IdealGasApp::simulation_speed_++;
  }
  if (event.getChar() == 's') {
    // decrease speed
    IdealGasApp::simulation_speed_--;
  }
}

void IdealGasApp::update() {
  for (int i = 0; i < IdealGasApp::simulation_speed_; i++) {
    histograms_.clear();
    container_.AdvanceOneFrame();
    CreateHistogram(container_);
    for (SpeedHistogram& histogram : histograms_) {
      histogram.AdvanceOneFrame();
    }
  }
}

}  // namespace idealgas
