#include "gas_simulation_app.h"
#include <iostream>


namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  container_.AddParticles(30, 3, 4, 1, ci::Color("white"));
  container_.AddParticles(30,2, 6, 3, ci::Color("orange"));
  container_.AddParticles(30,1, 9, 5, ci::Color("blue"));
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
  histogram_.Display();
}

void IdealGasApp::keyDown(cinder::app::KeyEvent event) {
  if( event.getChar() == 'w' ) {
    // increase speed
    IdealGasApp::simulation_speed_++;
  }
  if( event.getChar() == 's' ) {
    // decrease speed
    IdealGasApp::simulation_speed_--;
  }
}

void IdealGasApp::update() {
  for (int i = 0; i < IdealGasApp::simulation_speed_; i++) {
    container_.AdvanceOneFrame();
    histogram_.UpdateParticles(container_.GetParticles());
    histogram_.AdvanceOneFrame();
  }
}

}  // namespace idealgas
