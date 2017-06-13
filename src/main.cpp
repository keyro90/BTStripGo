#include <Arduino.h>
#include "utility_array.h"
#include "utility.h"
#include "utility_bt.h"
#include <GStripLed.h>
#include <SoftwareSerial.h>

GStripLed gs(3, 5, 6);
SoftwareSerial bt(8,9);
String line = "";
uint8_t values[3] = {0, 0, 0}, save_values[3] = {0, 0, 0};
uint16_t interr = 0;
unsigned long timer;
bool is_first_interr = true, counter_interr = false;

void setParameter(const char& det_color, const String& value){
  uint8_t pos = -1;
  if (line.length() > 0){
    switch(det_color){
      case 'Q':
        memset(values, 0, 3);
        interr = 0;
      case 'R':
        values[pos = 0] = value.toInt();
        break;
      case 'G':
        values[pos = 1] = value.toInt();
        break;
      case 'B':
        values[pos = 2] = value.toInt();
        break;
      case 'I':
        interr = value.toInt();
    }//switch
    if (pos >= 0 && interr > 0)
      save_values[pos] = values[pos];
  }//if-line
}

void detectInterrupt(){
  if (interr > 0){
     if (millis() - timer > interr){
       _debug("Passati "+String(interr)+" secondi.");
         if (is_first_interr){
           memcpy(save_values, values, 3*sizeof(uint8_t));
           is_first_interr = false;
         }
         (!counter_interr) ? (memset(values, 0, 3)) : ( memcpy(values, save_values, 3*sizeof(uint8_t)));
         counter_interr = !counter_interr;
         _debug("counter : "+String(counter_interr));
         timer = millis();
       _debug(String(values[0])+" "+String(values[1])+" "+String(values[2]));
     }//millis-interr
  }//if-inter
  else{
    if (sum_array(save_values, 3) > 0){
      memcpy(values, save_values, 3*sizeof(uint8_t));
      memset(save_values, 0, 3);
    }//if-sumarray
    is_first_interr = true;
    counter_interr = false;
  }//else
}

void setup(){
  if (DEBUG){
    Serial.begin(9600);
    _debug(line);
    _debug(gs);
  }
  bt.begin(9600);
  gs.init();
  timer = millis();
}//setup

void loop (){
  char det_color;
  String value;
  line = getLineBT(bt, &det_color, &value);
  setParameter(det_color, value);
  detectInterrupt();
  gs.write(values);
  _debug(gs);
  line = "";
}//loop
