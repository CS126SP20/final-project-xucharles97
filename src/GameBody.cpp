//
// Created by School on 4/30/20.
//

#include "mylibrary/GameBody.h"
#include "cinder/gl/gl.h"
#include "mylibrary/ConversionUtils.h"
#include "cinder/app/App.h"

using cinder::Color;

GameBody::GameBody(b2Body* body, b2Vec2 position, float bodyWidth, float bodyHeight, float r, float g, float b) {
  this->position = position;
  this->width = bodyWidth;
  this->height = bodyHeight;
  this->body = body;
  shape.SetAsBox(width, height);
  this->body->CreateFixture(&shape, 0.0f);
  red = r;
  green = g;
  blue = b;
}

void GameBody::draw() {
  vec2 pos = Conversions::toScreen(body->GetPosition());
//  gl::pushModelMatrix();
//  gl::translate(pos);

//  glPushMatrix();
//  gl::translate(pos);

  cinder::gl::color(red, green, blue);
  float widthToDraw = Conversions::dimensionsToScreen(width) / 2;
  float heightToDraw = Conversions::dimensionsToScreen(height) / 2;
//  std::cout << "Body position: (" << pos.x << ", " << pos.y << ") widthToDraw: " << std::to_string(widthToDraw) << " heightToDraw: " << std::to_string(heightToDraw) << std::endl;
//  std::cout << "rect coordinates: (" << std::to_string(pos.x - widthToDraw) << ", " << std::to_string(pos.y - heightToDraw) << ", " << std::to_string(pos.x + widthToDraw) << ", " << std::to_string(pos.y + heightToDraw) << std::endl;

  Rectf rect(pos.x - widthToDraw, pos.y - heightToDraw, pos.x + widthToDraw, pos.y + heightToDraw);
  gl::drawSolidRect(rect);
//  gl::popModelMatrix();

}
b2Vec2 GameBody::getPosition() { return position; }

float GameBody::getWidth() { return width; }

float GameBody::getHeight() { return height; }

//GameBody::GameBody(b2Body* body, float bodyWidth, float bodyHeight) {
//  if (body->GetType() == b2_dynamicBody) {
//
//    shape.SetAsBox(bodyWidth, bodyHeight);
//    fixtureDef.shape = &shape;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.3f;
//    this->body = body;
//    this->body->CreateFixture(&fixtureDef);
//
//  } else {
//    GameBody(body, body->GetPosition(), width, height);
//  }
//}

GameBody::GameBody() {
  red = 0.0f;
  green = 1.0f;
  blue = 0.0f;
}

void GameBody::setColor(float r, float g, float b) {
  red = r;
  green = g;
  blue = b;
  std::cout << "color" << std::endl;
}
