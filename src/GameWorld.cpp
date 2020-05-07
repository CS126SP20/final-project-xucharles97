//
// Created by School on 4/28/20.
//

#include "mylibrary/GameWorld.h"

#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>
#include <mylibrary/GameBody.h>

#include "mylibrary/ConversionUtils.h"

GameWorld::GameWorld() {
  // Define the gravity vector.
  b2Vec2 gravity(0.0f, 12.0f);

  // Construct a world object, which will hold and simulate the rigid bodies.
  world.SetGravity(gravity);
  timeStep = 1.0f / 60.0f;
  velocityIterations = 6;
  positionIterations = 2;

  world.SetContactListener(&contactListener);
}

void GameWorld::CreateBody(b2BodyDef body) {
  CreateBody(100.0f, 50.0f, body.position);

}

void GameWorld::CreateBody(float width, float height, b2Vec2 position) {
  CreateBody(width, height, position.x, position.y, 0.0f, 1.0f, 0.0f);

}

void GameWorld::CreateBody(float width, float height, float xCoord, float yCoord) {
  CreateBody(width, height, xCoord, yCoord, 0.0f, 1.0f, 0.0f);
}

void GameWorld::CreateBody(float width, float height, float xCoord,
                           float yCoord, float red, float green, float blue) {
  b2BodyDef bodyDef;
  bodyDef.position.Set(Conversions::toPhysics(xCoord), Conversions::toPhysics(yCoord));
  b2Body* body = world.CreateBody(&bodyDef);
  GameBody newBody(body, Conversions::toPhysics(b2Vec2(xCoord, yCoord)), Conversions::dimensionsToPhysics(width), Conversions::dimensionsToPhysics(height), red, green, blue);
  bodies.push_back(newBody);
  b2PolygonShape box;
  box.SetAsBox(newBody.getWidth(), newBody.getHeight());
  body->CreateFixture(&box, 0.0);
//  newBody.setColor(red, green, blue);
}

void GameWorld::Step(float32 timeStep, int32 velocityIterations, int32 positionIterations) {
  world.Step(timeStep, velocityIterations, positionIterations);
//  std::cout << "Player position in GameWorld: (" << playerBody->GetPosition().x << ", " << playerBody->GetPosition().y << ")" << std::endl;

}

bool GameWorld::Step(bool left, bool right, bool up, bool down) {
  player.processDirectionalInput(left, right, up, down);
  world.Step(timeStep, velocityIterations, positionIterations);
  return playerAtEnd();
}

void GameWorld::draw() {
  for (auto iter = bodies.begin(); iter != bodies.end(); iter++) {
    iter->draw();
  }
  player.draw();

  //draw the endpoint
  cinder::gl::color(1.0f, 1.0f, 1.0f);
  vec2 endPointPos = Conversions::toScreen(endPoint);
  Rectf rect(endPointPos.x - 25.0f, endPointPos.y - 25.0f, endPointPos.x + 25.0f, endPointPos.y + 25.0f);
  cinder::gl::drawSolidRect(rect);

}
void GameWorld::setPlayer(float posX, float posY) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(Conversions::toPhysics(posX), Conversions::toPhysics(posY));
  playerBody = world.CreateBody(&bodyDef);

//  // Define another box shape for the player
//  b2PolygonShape dynamicBox;
//  dynamicBox.SetAsBox(50.0f, 50.0f);
//
//  b2FixtureDef fixtureDef;
//  fixtureDef.shape = &dynamicBox;
//  fixtureDef.density = 1.0f;
//  fixtureDef.friction = 0.3f;
//  player->CreateFixture(&fixtureDef);

  player = PlayerBody (playerBody, Conversions::dimensionsToPhysics(50.0f), Conversions::dimensionsToPhysics(50.0f));
  std::cout << "made player!" << std::endl;
}

PlayerBody GameWorld::getPlayer() {
  return player;
}

void GameWorld::setEndPoint(float xCoord, float yCoord) {
  this->endPoint.x = Conversions::toPhysics(xCoord);
  this->endPoint.y = Conversions::toPhysics(yCoord);
}

bool GameWorld::playerAtEnd() {
  return sqrt(pow(endPoint.x - player.getPhysicsPosition().x , 2) +
              pow(endPoint.y - player.getPhysicsPosition().y, 2)) < 1.0f;
}
void GameWorld::setWorldBottom(float newBottom) {
  this->worldBottom = Conversions::toPhysics(newBottom);
}
bool GameWorld::playerFellThroughPit() {
  return (player.getPhysicsPosition().y > worldBottom);
}


//void GameWorld::addPlayer(b2BodyDef newPlayer) {
//  newPlayer.type = b2_dynamicBody;
//  b2Body* newPlayerBody = world.CreateBody(&newPlayer);
//  b2PolygonShape newPolygon;
//  newPolygon.SetAsBox(5.0f, 5.0f);
//  b2FixtureDef newFixture;
//  newFixtu
//}
