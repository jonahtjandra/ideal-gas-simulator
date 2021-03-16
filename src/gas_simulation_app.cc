#include "gas_simulation_app.h"
#include <iostream>


namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
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
  }
}

}  // namespace idealgas
