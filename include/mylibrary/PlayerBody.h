//
// Created by School on 5/5/20.
//

#ifndef FINALPROJECT_PLAYERBODY_H
#define FINALPROJECT_PLAYERBODY_H

#include "GameBody.h"

class PlayerBody : public GameBody {
 public:
  //Constructors
  PlayerBody();
  PlayerBody(b2Body* body, float width, float height);

  //used to keep track of the player's horizontal direction
  enum direction {DIR_LEFT, DIR_RIGHT, DIR_STOP};

  //methods to take in a directional input (or lack thereof) and move the player appropriately
  void processDirectionalInput(bool leftInput, bool rightInput, bool upInput, bool downInput);
  void jump();
  void moveLeft();
  void moveRight();
  void stopHorizontally();

  //keeps track if the player is on the ground
  void touchedGround();
//  void leftGround();
  bool isFalling();


  //gets the position with respect to the Box2D and screen coordinates
  b2Vec2 getPhysicsPosition();
  ci::vec2 getScreenPosition();

  //sets the position of the player
  void setPosition(b2Vec2 newPosition);
  void setPosition(float newX, float newY);



 private:
  //maximum number of jumps a player can do
  int maxJumps;
  //current number of jumps a player has. Resets when on the ground
  int numJumps;
  //keeps track of if a player is on the ground
  bool isTouchingGround;
  //used to detect when the player collides with another body
  b2PolygonShape footShape;
  b2FixtureDef footFixtureDef;
  b2Fixture* footSensor;
  //horizontal drift
  float maxHorizontalSpeed = 6.0f;
  float jumpHeight;
  //used to keep track of whether or not the player is falling based on acceleration
  float previousYVelocity;

  //the player's current horizontal direction
  direction currentDirection;




};

#endif  // FINALPROJECT_PLAYERBODY_H
