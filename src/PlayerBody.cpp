//
// Created by School on 5/5/20.
//

#include "mylibrary/PlayerBody.h"

#include <mylibrary/ConversionUtils.h>

PlayerBody::PlayerBody() {
  setColor(1.0f, 0.0f, 0.0f);
  numJumps = 2;
  currentDirection = DIR_STOP;
}

PlayerBody::PlayerBody(b2Body* bodyInput, float bodyWidth, float bodyHeight) {

  //set up main body
  bodyInput->SetType(b2_dynamicBody);
  width = bodyWidth;
  height = bodyHeight;
  this->body = bodyInput;
  shape.SetAsBox(width, height);
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  this->body->CreateFixture(&fixtureDef);
  body->SetFixedRotation(true);



  footShape.SetAsBox(width, height, b2Vec2(0, -height), 0);
  footFixtureDef.shape = &footShape;
  footFixtureDef.isSensor = true;
  footSensor = body->CreateFixture(&footFixtureDef);
  footSensor->SetUserData(this);
//  body->SetUserData(this);


  setColor(1.0f, 0.0f, 0.0f);
  maxJumps = 2;
  numJumps = maxJumps;
  currentDirection = DIR_STOP;

  this->body->SetUserData(this);

  isTouchingGround = true;

  previousYVelocity = 0.0f;

  jumpHeight = 7.0f;

}

void PlayerBody::processDirectionalInput(bool leftInput, bool rightInput,
                                         bool upInput, bool downInput) {
//  std::cout << "up: " << std::to_string(upInput) << " down: " << std::to_string(downInput) << " left: " << std::to_string(leftInput) << " right: " << std::to_string(rightInput) << std::endl;

//  if (body.)

  //if you just landed
  if (!isFalling() && previousYVelocity != 0) {
    isTouchingGround = true;
    numJumps = maxJumps;
  }

  if (upInput) {
    jump();
  }

  previousYVelocity = body->GetLinearVelocity().y;

  //Process right and left inputs
  //Right will always override left
  if (rightInput) {
    moveRight();
  } else if (leftInput) {
    moveLeft();
  } else {
    stopHorizontally();
  }

//  std::cout << "Player velocity: (" << body->GetLinearVelocity().x << ", " << body->GetLinearVelocity().y << std::endl;

}

void PlayerBody::jump() {
  if (numJumps <= 0) {
    return;
  }
//  std::cout << "jump" << std::endl;

  if (isTouchingGround) {
    float impulse = body->GetMass() * -jumpHeight;
    body->ApplyLinearImpulse( b2Vec2(0,impulse), body->GetPosition());
  } else {
//    impulse *= -0.6f * jumpHeight;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.y = -0.95 * jumpHeight;
//  velocity.x = 0;
    body->SetLinearVelocity(velocity);
  }

  numJumps--;
  std::cout << "numJumps: " << std::to_string(numJumps) << std::endl;
  isTouchingGround = false;
}
void PlayerBody::moveLeft() {
  b2Vec2 velocity = body->GetLinearVelocity();
  velocity.x = -1 * maxHorizontalSpeed;
  body->SetLinearVelocity(velocity);
  currentDirection = DIR_LEFT;
}
void PlayerBody::moveRight() {
  b2Vec2 velocity = body->GetLinearVelocity();
  velocity.x = maxHorizontalSpeed;
  body->SetLinearVelocity(velocity);
  currentDirection = DIR_RIGHT;
}

void PlayerBody::stopHorizontally() {
  b2Vec2 velocity = body->GetLinearVelocity();
  velocity.x *= .95;
//  velocity.x = 0;
  body->SetLinearVelocity(velocity);
  currentDirection = DIR_STOP;
}

b2Vec2 PlayerBody::getPhysicsPosition() {
//  std::cout << "PlayerBody Position: (" << this->body->GetPosition().x << ", " << this->body->GetPosition().y << ")" << std::endl;
  return this->body->GetPosition();
}

ci::vec2 PlayerBody::getScreenPosition() {
//  std::cout << "footSensor Position (Physics): (" << this->footSensor << ", " << this->body->GetPosition().y << ")" << std::endl;
//  std::cout << isTouchingGround << std::endl;
  return Conversions::toScreen(this->body->GetPosition());
}

void PlayerBody::setPosition(b2Vec2 newPosition) {
  this->position = newPosition;
}

void PlayerBody::setPosition(float newX, float newY) {
  this->position.x = newX;
  this->position.y = newY;
}
void PlayerBody::touchedGround() {
//  std::cout << "LANDED" << std::endl;
  isTouchingGround = true;
//  if (isTouchingGround) {
//    std::cout << "isTouchingGround" << std::endl;
//  } else {
//    std::cout << "didn't Touch Ground" << std::endl;
//  }

//  numJumps = maxJumps;
//
//  std::cout << "numJumps: " << std::to_string(numJumps) << std::endl;
//  std::cout << "maxJumps: " << std::to_string(maxJumps) << std::endl;
}
//void PlayerBody::leftGround() {
//  isTouchingGround = false;
//}
bool PlayerBody::isFalling() {
  bool falling = true;
  float currentYVelocity = body->GetLinearVelocity().y;

  if (currentYVelocity == 0 && currentYVelocity < previousYVelocity) {
    falling = false;
  }
  return falling;
}
