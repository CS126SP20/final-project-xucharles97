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

  void Jump();
  void MoveLeft();
  void MoveRight();

 private:
  int numJumps;


};

#endif  // FINALPROJECT_PLAYERBODY_H
