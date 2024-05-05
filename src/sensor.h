#ifndef sensor_h
#define sensor_h
#include "Arduino.h"

class Transdutor{
    public:
        Transdutor(int8_t pin_used, int mim_value, int max_value, int8_t pin_alarm);
        double read_preassure();
        void alarm_on();
        void alarm_off();
    private:
        int8_t __pin;
        int8_t __alarm_pin;
        int __mim_preassure;
        int __max_preassure;
};



#endif