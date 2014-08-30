/*
  ButtonTracker.cpp - Library for tracking short & long presses of a button
  Created by Andy Swing, August 29, 2014.
  Released into the public domain.
*/

#include "ButtonTracker.h"

// Constructor
ButtonTracker::ButtonTracker(){
    curValue = false;
    prevValue = false;
    posEdgeTime = 0;
    negEdgeTime = 0;
    edgeDelta = 0;
    isShort = false;
    isLong = false;
    isHold = false;
}

// Set minimum duration for a short tap to count
void ButtonTracker::setShortTapMin(unsigned int timeInMs){
    shortTapMinMs = timeInMs;
}

// Set minimum duration for a long tap to count
void ButtonTracker::setLongTapMin(unsigned int timeInMs){
    longTapMinMs = timeInMs;
}

// Set threshold for a press to be counted as a hold
void ButtonTracker::setHoldMin(unsigned int timeInMs){
    holdMinMs = timeInMs;
}

// Update with a (possibly) new value
// Pass in "true" when button is pressed, "false" when released
void ButtonTracker::update(bool value){

    prevValue = curValue;
    curValue = value;
    
    // Clear any previous event
    isShort = isLong = isHold = false;
    
    // Edge detect
    if(prevValue != curValue){
        // Rising edge (button pressed)
        if(curValue){
            posEdgeTime = millis();
        }
        // Falling edge (button released)
        else{
            // Record event time & compute delta
            negEdgeTime = millis();
            edgeDelta = negEdgeTime - posEdgeTime;
            // Determine classification
            if(edgeDelta >= holdMinMs){
                isHold=true;
            } else if(edgeDelta >= longTapMinMs){
                isLong=true;
            } else if(edgeDelta >= shortTapMinMs){
                isShort=true;
            }
            // else too short to count
        }
    }
}

bool ButtonTracker::wasShort(){
    return isShort;
}

bool ButtonTracker::wasLong(){
    return isLong;
}

bool ButtonTracker::wasHold(){
    return isHold;
}