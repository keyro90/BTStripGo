#ifndef UTILITY_ARRAY_H
#define UTILITY_ARRAY_H

#include <Arduino.h>

bool array_cmp(uint8_t *a1, uint8_t *a2, unsigned long len){
  for (unsigned long i=0; i<len; i++)
    if (a1[i] != a2[i])
      return false;
  return true;
}

bool sum_array(uint8_t *a1, unsigned long len){
  unsigned long sum = 0;
  for (unsigned long i=0; i<len; i++)
    sum += a1[i];
  return sum;
}

#endif
