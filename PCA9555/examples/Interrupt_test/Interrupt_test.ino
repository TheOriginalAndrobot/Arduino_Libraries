#include <Wire.h>
#include "PCA9555.h"


const int ledPin = 13;
const int intPin = 19;
const int intNum = 4;   // Pin 19 is int.4 on Mega
bool status;
volatile bool newData = false;

PCA9555 myDev(0x00);

void setup() {

    pinMode(ledPin, OUTPUT);
    pinMode(intPin, INPUT);

    // initialize serial communication at 9600 bits per second:
    Serial.begin(115200);
    Serial.println("Started!");

    Wire.begin();

    status = myDev.begin();
    status &= myDev.setPolarity(0xFFFF);

    digitalWrite(ledPin, status);
    if (!status) {
        Serial.println("Error initializing device!");
    } else {
        Serial.println("Device inititialized.");
    }
    
    attachInterrupt(intNum, edgeHandler, FALLING);
}



void loop(){
    if(newData){
        newData = false;
        status = myDev.read();
        if(status && myDev.getChanged() != 0) {
            Serial.print("New state: 1b");
            Serial.println(myDev.getValues(), BIN);
        }
        
    }
}

void edgeHandler() {
    newData = true;
}
