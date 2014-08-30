#include <Wire.h>
#include "ButtonTracker.h"

const int buttonPin = 12;

ButtonTracker myBT;
bool state;

void setup() {
  
    pinMode(buttonPin,  INPUT_PULLUP);
  
    Serial.begin(115200);
    Serial.println("ButtonTracker test started");
}

void loop(){
    
    // Active low button
    state = digitalRead(buttonPin) ? 0:1;
    
    // Update the tracker
    myBT.update(state);
    
    if (myBT.wasShort()) {
        Serial.println("Short");
    } else if (myBT.wasLong()) {
        Serial.println("Long");
    } else if (myBT.wasHold()) {
        Serial.println("Hold");
    }
    
    delay(1);
}
