//
// Created by School on 4/30/20.
//

#ifndef FINALPROJECT_GAMEBODY_H
#define FINALPROJECT_GAMEBODY_H

#include <Box2D/Box2D.h>
#include <cinder/Color.h>

using cinder::Color;

class GameBody {
 public:
  //constructors
  GameBody();
  GameBody(b2Body* body, b2Vec2 position, float width, float height, float red, float green, float blue);

  /**
   * draws the body
   * virtual so that PlayerBody can override it
   */
  virtual void draw();

  //getters
  b2Vec2 getPosition();
  float getWidth();
  float getHeight();

  //setters
  void setColor(float r, float g, float b);


 protected:
  b2Vec2 position; //position based on the Box2D simulation
  b2Body* body;
  float width; //width and height in physics dimensions
  float height;
  b2PolygonShape shape;
  b2FixtureDef fixtureDef;
  float red;
  float green;
  float blue;
};

#endif  // FINALPROJECT_GAMEBODY_H
