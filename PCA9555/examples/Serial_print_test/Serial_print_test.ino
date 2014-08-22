#include <Wire.h>
#include "PCA9555.h"


int ledPin = 13;
int intPin = 19;
bool status;

PCA9555 myDev(0x00);

void setup() {
  
  pinMode(ledPin, OUTPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  Wire.begin();

  status = myDev.begin();
  status &= myDev.setPolarity(0xFFFF);
  digitalWrite(ledPin, status);

}



void loop()
{
    status = myDev.read();
    
    if (!status) {
      
      Serial.println("Error!");
      
    } else if(myDev.getChanged() != 0) {
      
      Serial.print("New state: 1b");
      Serial.println(myDev.getValues(), BIN);
      
    }
    
    delay(1);        // delay in between reads for stability
  
}
