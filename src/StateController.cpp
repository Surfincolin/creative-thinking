//
//  StateController.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/22/17.
//
//

#include "StateController.hpp"

using namespace ct;

StateController::StateController() {
  
}

void StateController::nextState() {
  state += 1;
  
  if (state > 6) {
    state = 0;
  }
  
}

void StateController::startOver() {
  state = 0;
}

int StateController::getState() {
  return state;
}
