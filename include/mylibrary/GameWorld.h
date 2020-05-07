//
// Created by School on 4/28/20.
//

#ifndef FINALPROJECT_GAMEWORLD_H
#define FINALPROJECT_GAMEWORLD_H

#include <Box2D/Box2D.h>

#include <vector>

#include "ContactListener.h"
#include "GameBody.h"
#include "PlayerBody.h"

class GameWorld {
 public:
  //constructor
  GameWorld();

  //creates a new GameBody to add to the world
  //stores in the bodies vector
  void CreateBody(b2BodyDef body);
  void CreateBody(float width, float height, b2Vec2 position);
  void CreateBody(float width, float height, float xCoord, float yCoord);
  void CreateBody(float width, float height, float xCoord, float yCoord, float red, float green, float blue);

  //updates the GameWorld
  void Step(float32 timeStep, int32 velocityIterations, int32 positionIterations);

  /** updates the GameWorld based on the directional inputs
   * paramaters are true if that respective direction was inputted, false if otherwise
   * @return true if the player completed the level, false if otherwise
   */
  bool Step(bool left, bool right, bool up, bool down);

  //draws all the elements in the world
  void draw();
  PlayerBody getPlayer();
  /** sets/creates the player object for the world by taking in the coordinates for it
   * parameters are in screen coordinates
   */
  void setPlayer(float posX, float posY);
  //stores all the non-player GameBodies
  std::vector<GameBody> bodies;

  /** sets the end point/goal for the player
   * parameters are in screen coordinates
   */
  void setEndPoint(float xCoord, float yCoord);
  /** detects if the player is within a certain distance from the goal
   * returns true if the player is close enough, false otherwise
   */
  bool playerAtEnd();

  //meant for creating bottomless pits
  //was never able to integrate it
  void setWorldBottom(float newBottom);
  bool playerFellThroughPit();

 private:
  b2Vec2 gravity;
  //the world that stores all the simulation data
  b2World world = b2World(b2Vec2());
  //the PlayerBody that stores all the data related to the player
  PlayerBody player;
  b2Body* playerBody;

  //intervals to simulate the world to
  float32 timeStep;
  int32 velocityIterations;
  int32 positionIterations;

  //detects when two objects collide
  ContactListener contactListener;

  //position of the endpoint (in Box2D coordinates)
  b2Vec2 endPoint;

  //y-value threshold for a bottomless pit
  float worldBottom; //in physics form




};

#endif  // FINALPROJECT_GAMEWORLD_H
