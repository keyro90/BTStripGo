#ifndef GSTRIPLED_H
#define GSTRIPLED_H

#include <Arduino.h>

enum GSColor {GSRED = 0, GSGREEN = 1, GSBLUE = 2};

class GStripLed{

  private:
    uint8_t pin_led[3];
    uint8_t value_led[3];

    void checkInterrupt();

  public:

    GStripLed(uint8_t r, uint8_t g, uint8_t b);

    GStripLed(uint8_t * colors);

    void init();

    void write (GSColor c, uint8_t value);

    void write (uint8_t pos, uint8_t value);

    void write (uint8_t * value);

    void reset();

    bool isLightOff();

    uint8_t * getValues();

    uint8_t * getPins();

    bool operator== (const uint8_t *invalues);

    bool operator== (const GStripLed &invalues);

    operator String();


};

#endif
