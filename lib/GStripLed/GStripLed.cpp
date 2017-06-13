#include "GStripLed.h"
#include <Arduino.h>

GStripLed::GStripLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b){
  pin_led[0] = pin_r;
  pin_led[1] = pin_g;
  pin_led[2] = pin_b;
}

GStripLed::GStripLed(uint8_t * pin_colors){
  GStripLed(pin_colors[0], pin_colors[1], pin_colors[2]);
}

void GStripLed::init(){
  for (int i=0; i<3; i++){
    pinMode(pin_led[i], OUTPUT);
    analogWrite(pin_led[i], value_led[i] = 0);
  }//for
}

void GStripLed::write (GSColor c, uint8_t value){
  if (c >= 0 && c <= 2)
    analogWrite(pin_led[c], value_led[c] = constrain(value, 0, 255));
}

void GStripLed::write (uint8_t * values){
  for (int i=0; i<3; i++)
    analogWrite(pin_led[i], value_led[i] = constrain(values[i], 0, 255));
}

void GStripLed::reset(){
  uint8_t zeros[3] = {0, 0, 0};
  write(zeros);
}

uint8_t * GStripLed::getValues(){
  return value_led;
}

uint8_t * GStripLed::getPins(){
  return pin_led;
}

bool GStripLed::isLightOff(){
  return value_led[0] == 0 && value_led[1] == 0 && value_led[2] == 0;
}

bool GStripLed::operator== (const uint8_t *invalues){
  return value_led[0] == invalues[0] && value_led[1] == invalues[1] && value_led[2] == invalues[2];
}

bool GStripLed::operator== (const GStripLed &invalues){
  return value_led[0] == invalues.value_led[0] && value_led[1] == invalues.value_led[1] && value_led[2] == invalues.value_led[2];
}

GStripLed::operator String(){
  String s = "";
  for (int i=0; i<3; i++)
    s += String(pin_led[i])+" : "+String(value_led[i])+", ";
  s.remove(s.length()-1);
  return s;
}
