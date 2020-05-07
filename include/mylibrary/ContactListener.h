//
// Created by School on 5/6/20.
//

#ifndef FINALPROJECT_CONTACTLISTENER_H
#define FINALPROJECT_CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

//struct Contact {
//  b2Fixture *fixtureA;
//  b2Fixture *fixtureB;
//  bool operator==(const Contact& other) const {
//    return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
//  }
//};

class ContactListener : public b2ContactListener {
 public:
  /**
   * Default Constructor
   */
  ContactListener();

 private:
  /** Called whenever two objects come into contact with each other
   * @param contact the b2Contac object containing the two bodies that collided
   */
  void BeginContact(b2Contact* contact);


};

#endif  // FINALPROJECT_CONTACTLISTENER_H
