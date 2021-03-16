#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * constructor for ideal gas app
   */
  IdealGasApp();

  /**
   * overriding draw method
   */
  void draw() override;
  /**
   * overriding update method
   */
  void update() override;
  /**
   * overriding keyDown method
   */
  void keyDown(cinder::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 610;

 private:
  GasContainer container_ = GasContainer(100, 1, 6, ci::Color("green"),600);
  //set speed of simulation
  int simulation_speed_ = 1;
};

}  // namespace idealgas
