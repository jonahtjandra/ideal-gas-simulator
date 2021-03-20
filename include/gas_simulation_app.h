#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "speed_histogram.h"

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
  const int kWindowSize = 750;

 private:
  //add comments
  GasContainer container_ = GasContainer(600);
  SpeedHistogram histogram_ = SpeedHistogram(container_.GetParticles(), 100, ci::Color("blue"), 10);
  //set speed of simulation
  int simulation_speed_ = 1;
};

}  // namespace idealgas
