/*
  ButtonTracker.h - Library for tracking short & long presses of a button
  Created by Andy Swing, August 29, 2014.
  Released into the public domain.
*/
#ifndef ButtonTracker_h
#define ButtonTracker_h

#include "Arduino.h"

class ButtonTracker
{
private:
    // Parameters
    unsigned int shortTapMinMs = 50;    // Minimum duration for short tap
    unsigned int longTapMinMs = 400;    // Minimum duration for long tap
    unsigned int holdMinMs = 2000;      // Minimum duration for a hold condition
    // State
    bool curValue;
    bool prevValue;
    unsigned long posEdgeTime;
    unsigned long negEdgeTime;
    unsigned long edgeDelta;
    bool isShort;
    bool isLong;
    bool isHold;
public:
    ButtonTracker();
    void setShortTapMin(unsigned int timeInMs);
    void setLongTapMin(unsigned int timeInMs);
    void setHoldMin(unsigned int timeInMs);
    void update(bool value);
    bool wasShort();
    bool wasLong();
    bool wasHold();
};

#endif