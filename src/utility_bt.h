#ifndef UTILITY_BT_H
#define UTILITY_BT_H

#include <Arduino.h>
#include <SoftwareSerial.h>

String getLineBT (SoftwareSerial &bt, char * opt, String * value){
  String rec = "";
  if (bt.available()){
    rec = bt.readStringUntil('!');
    rec.trim();
  }//if
  if (rec.length() > 0){
    (*opt) = rec[0];
    (*value) = rec.substring(1);
  }//if
  else{
    (*opt) = '-';
    (*value) = "";
  }//else
  return rec;
}

#endif
