//
// Created by School on 4/28/20.
//

#ifndef FINALPROJECT_CONVERSIONUTILS_H
#define FINALPROJECT_CONVERSIONUTILS_H

#pragma once
#include "cinder/Vector.h"
#include "Box2D/Box2D.h"

using namespace ci;

struct Conversions {

  /** The scaling from the physics engine to the screen
   * physics * scaling = screen
   */
  static float getScaling() {
    static float scaling = 50.0f; return scaling;
  }

  /** scales a vector from the physics scale to the appropriate screen size
   * @param fin vector to scale
   * @return scaled vector
   */
  static vec2 toScreen(b2Vec2 vec)
  {
    return vec2(vec.x, vec.y) * getScaling();
  }

  /** scales a vector from the screen size to the appropriate physics scale
   * @param vec the vector to scale down
   * @return scaled vector (in Box2D dimensions)
   */
  static b2Vec2 toPhysics(b2Vec2 vec)
  {
    return b2Vec2( vec.x/getScaling(), vec.y/getScaling() );
  }

  /** scales a scalar from the screen size to the appropriate physics scale
   * @param scal the scalar to scale down
   * @return scaled value (in Box2D dimensions)
   */
  static float toPhysics(float scal)
  {
    return scal / getScaling();
  }

  /** scales a scalar from the physics scale to the appropriate screen size
   * @param scal the scalar to scale down
   * @return scaled value (in screen dimensions)
   */
  static float toScreen(float scal)
  {
    return scal * getScaling();
  }

  /** scales a given dimension from screen size to physics
   * divides by the standard scale and by 2 because Box2D only takes half-dimensions
   * @param dimension dimension to scale down
   * @return the dimension scaled down (divided by 2 * getScaling())
   */
  static float dimensionsToPhysics(float dimension) {
    return dimension / (getScaling() * 2); //divide by 2 since Box2D shapes only store half lengths
  }

  /** scales a given dimension from physics scale to screen
   * multiplies by the standard scale and by 2 because Box2D only takes half-dimensions
   * @param dimension dimension to scale up
   * @return the dimension scaled up (multiplied by 2 * getScaling())
   */
  static float dimensionsToScreen(float dimension) {
    return dimension * getScaling() * 2; //divide by 2 since Box2D shapes only store half lengths
  }
};

#endif  // FINALPROJECT_CONVERSIONUTILS_H
