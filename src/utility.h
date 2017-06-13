#ifndef UTILITY_H
#define UTILITY_H
#define DEBUG 0

#include <Arduino.h>

void _debug(String s, bool wanted = DEBUG, bool nl = true){
  if (wanted){
      Serial.print(s);
    if (nl)
      Serial.println();
  }//if
}//_debug

#endif
