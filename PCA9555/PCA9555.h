/*
  PCA9555.h - Library for interfacing with a PCA9555 I2C I/O expander
  Created by Andy Swing, August 20, 2014.
  Released into the public domain.
*/
#ifndef PCA9555_h
#define PCA9555_h

#include "Arduino.h"

class PCA9555
{
private:
    static byte baseAddr = 0x20;    // 7-bit family address
    byte addr;                      // Full device address
    word curValues;
    word prevValues;
public:
    PCA9555(byte hwAddr);
    bool begin();
    bool setPolarity(word pol);
    bool setDirection(word dir);
    bool write(word data);
    bool read();
    word getValues();
    word getChanged();
};

#endif