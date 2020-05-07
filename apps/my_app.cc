// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/Color.h>
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

#include "mylibrary/GameBody.h"
#include "mylibrary/GameWorld.h"
#include "mylibrary/ConversionUtils.h"

namespace myapp {

using cinder::app::KeyEvent;
using std::cout;
using cinder::Color;
using cinder::Rectf;


MyApp::MyApp() :
  gravity{0.0f, -10.0f},
  world{gravity},
  width{800.0f},
  height{800.0f},
  timeStep{1.0f / 60.0f},
  velocityIterations{6},
  positionIterations{2},
  jumpCooldown{25} {}


void MyApp::setup() {
  upPressed, downPressed, leftPressed, rightPressed = false;


  demo.CreateBody(width, 150, width / 2, height - 75);

  demo.CreateBody(25, height, 0, height / 2);

  demo.CreateBody(25, height, width, height / 2);

  demo.CreateBody(100, height / 2, width / 2, height - 200);

  demo.CreateBody(250, height / 4, width / 2, height - 500);

  demo.setPlayer(125.0f, height - 150);

  demo.setEndPoint(width - 125.0f, height - 175.0f);

  levelPassed = false;
  timeUntilNextJump = 0;
}

void MyApp::update() {
//  cout << "update" << std::endl;
  if (timeUntilNextJump > 0) {
    timeUntilNextJump--;
  }

  if (demo.Step(leftPressed, rightPressed, upPressed, downPressed)) {
    levelPassed = true;
  }

  upPressed = false;

}

void MyApp::draw() {

  if (levelPassed) {
    //if you won, print a win message
    //copied from snake
    cinder::gl::clear(Color(0.0f, 1.0f, 0.0f));
    std::string text = "You win!";
    Color color = {0, 0, 0};
    cinder::ivec2 size = {300, 50};
    cinder::vec2 loc = {width / 2, height / 2};

    auto box = TextBox()
        .alignment(TextBox::CENTER)
        .font(cinder::Font("Arial Unicode MS", 30))
        .size(size)
        .color(color)
        .backgroundColor(ColorA(0, 0, 0, 0))
        .text(text);
    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);

  } else {
    cinder::gl::clear();
    drawWorld(demo);
  }


//  cinder::gl::color(1, 0, 0);
//  cinder::vec2 position = demo.getPlayer().getScreenPosition();
//  cout << "Player position: (" << position.x << ", " << position.y << ")" << std::endl;
//  float widthToDraw = Conversions::dimensionsToScreen(demo.getPlayer().getWidth()) / 2;
//  float heightToDraw = Conversions::dimensionsToScreen(demo.getPlayer().getHeight()) / 2;
//  Rectf rect(position.x - widthToDraw, position.y - heightToDraw, position.x + widthToDraw, position.y + heightToDraw);
//  cinder::gl::drawSolidRect(rect);
}

void MyApp::keyDown(KeyEvent event) {
//  upPressed, downPressed, leftPressed, rightPressed = false;
//  cout << "keyDown code: " << std::to_string(event.getChar()) << std::endl;

  int code = event.getCode();
  if (code == KeyEvent::KEY_UP || code == KeyEvent::KEY_w) {
      if (timeUntilNextJump <= 0) {
        upPressed = true;
        timeUntilNextJump = jumpCooldown;
      }
  }

  if (code == KeyEvent::KEY_DOWN || code == KeyEvent::KEY_s) {
    downPressed = true;
  }

  if (code == KeyEvent::KEY_LEFT || code == KeyEvent::KEY_a) {
    leftPressed = true;
  }

  if (code == KeyEvent::KEY_RIGHT || code == KeyEvent::KEY_d) {
    rightPressed = true;
  }

}

void MyApp::keyUp(KeyEvent event) {
  int code = event.getCode();
  if (code == KeyEvent::KEY_UP || code == KeyEvent::KEY_w) {
    upPressed = false;
  }

  if (code == KeyEvent::KEY_DOWN || code == KeyEvent::KEY_s) {
    downPressed = false;
  }

  if (code == KeyEvent::KEY_LEFT || code == KeyEvent::KEY_a) {
    leftPressed = false;
  }

  if (code == KeyEvent::KEY_RIGHT || code == KeyEvent::KEY_d) {
    rightPressed = false;
  }
}

void MyApp::drawWorld(GameWorld & gameWorld) { gameWorld.draw(); }

}  // namespace myapp
