/*
  PCA9555.cpp - Library for interfacing with a PCA9555 I2C I/O expander
  Created by Andy Swing, August 20, 2014.
  Released into the public domain.
*/

#include "PCA9555.h"

// Constructor
PCA9555::PCA9555(byte hwAddr)
{
    addr = baseAddr | (hwAddr & 0x07);
    curValues = 0x0000;
    prevValues = 0x0000;
}

// Init the device
// Returns true if successful
bool PCA9555::begin()
{
    bool status = true;

    status &= write(0x0000);        // Set outputs low
    status &= setPolarity(0x0000);  // Default to normal polarity
    status &= setDirection(0xFFFF); // Default to all inputs
    status &= read();               // Read initial values

    return status;
}

// Set input pin polarity inversion (0=normal, 1=inverted)
// Returns true if successful
bool PCA9555::setPolarity(word pol)
{
    int status;

    Wire.beginTransmission(addr);
    Wire.write(0x04);            // Register 4
    Wire.write(pol & 0x00FF);    // Pins 7..0
    Wire.write(pol>>8);          // Pins 15..8
    status = Wire.endTransmission();

    // Re-read initial values & reset any events
    read();
    prevValues = curValues;

    return (status == 0);
}

// Set pin direction (0=output, 1=input)
// Returns true if successful
bool PCA9555::setDirection(word dir)
{
    int status;

    Wire.beginTransmission(addr);
    Wire.write(0x06);            // Register 6
    Wire.write(dir & 0x00FF);    // Pins 7..0
    Wire.write(dir>>8);          // Pins 15..8
    status = Wire.endTransmission();

    // Re-read initial values & reset any events
    read();
    prevValues = curValues;

    return (status == 0);
}

// Write output pin data
// Returns true if successful
bool PCA9555::write(word data)
{
    int status;

    Wire.beginTransmission(addr);
    Wire.write(0x02);            // Register 2
    Wire.write(data & 0x00FF);   // Pins 7..0
    Wire.write(data>>8);         // Pins 15..8
    status = Wire.endTransmission();

    return (status == 0);
}

// Read input pin state, store it into curValues
// Returns true if successful
bool PCA9555::read()
{
    int status = 0;
    byte b0;
    byte b1;

    // Even if the read fails, we will clear out any changes
    prevValues = curValues;

    // Set register to zero for later reading
    Wire.beginTransmission(addr);
    Wire.write(0x00);
    status += Wire.endTransmission();

    // Attempt to read two bytes
    if (!status && Wire.requestFrom(addr, (byte)2) == 2){
        b0 = Wire.read();
        b1 = Wire.read();
        curValues = word(b1, b0);
    }

    return (status == 0);
}

// Return last read input values
word PCA9555::getValues()
{
    return curValues;
}

// Return bits that changed on last read
word PCA9555::getChanged()
{
    return (prevValues ^ curValues);
}

