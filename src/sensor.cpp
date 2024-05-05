#include "Arduino.h"
#include "sensor.h"

Transdutor::Transdutor(int8_t pin_used, int mim_value, int max_value, int8_t pin_alarm){
      __pin = pin_used;
      __alarm_pin = pin_alarm;
      pinMode(__alarm_pin, OUTPUT);
      __mim_preassure = mim_value;
      __max_preassure = max_value;
    };


double Transdutor::read_preassure(){
      int val = analogRead(__pin);
      double preassure = val*__max_preassure/1023.0;
      return preassure;
    };

void Transdutor::alarm_on(){
  digitalWrite(__alarm_pin, HIGH);
};

void Transdutor::alarm_off(){
  digitalWrite(__alarm_pin, LOW);
};


