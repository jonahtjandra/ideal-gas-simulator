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
  void CreateHistogram(const GasContainer container_);
  //add comments
  GasContainer container_ = GasContainer(600);
  std::vector<SpeedHistogram> histograms_;
  //set speed of simulation
  int simulation_speed_ = 1;
  ci::Color particle_color_1 = ci::Color("white");
  ci::Color particle_color_2 = ci::Color("orange");
  ci::Color particle_color_3 = ci::Color("blue");
};

}  // namespace idealgas
