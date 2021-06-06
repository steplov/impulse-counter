#include "Arduino.h"
#include <RunningAverage.h>

#ifndef METER_H
#define METER_H

class Meter
{
  public:
    Meter(unsigned int pulses_per_kwh);
    
    void pulse();
    double get_power();
    double get_elapsed_energy();

    volatile unsigned long pulse_length;
    volatile unsigned long count;

  private:
    volatile unsigned int _pulses_per_kwh;
    volatile unsigned long _pulse_time;
    volatile unsigned long _last_pulse_time;
};

#endif
