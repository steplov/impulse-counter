#include "Meter.h"
#include "Arduino.h"

Meter::Meter(unsigned int pulses_per_kwh)
: _pulses_per_kwh(pulses_per_kwh)
, count(0) {
}

// interrupt callback
void Meter::pulse()
{  
  // used to measure time between pulses.
  _pulse_time = millis();
  
  // increment pulse count
  count++;
  
  // calculate pulse length
  pulse_length = _pulse_time - _last_pulse_time;
  
  // remember pulse time for next time
  _last_pulse_time = _pulse_time;
}

double Meter::get_power() {
  unsigned long current_pulse_length = millis() - _last_pulse_time;
  
  // if current pulse is shorter than previous whole pulse, then we haven't had a pulse yet
  // so use previous whole pulse length instead.
  if (current_pulse_length < pulse_length) current_pulse_length = pulse_length;
  
  // calculate power based on pulse length
  return pulse_length == 0
    ? 0
    : (1000.0 / _pulses_per_kwh) * 3600.0 / pulse_length * 1000.0;
}

double Meter::get_elapsed_energy() {
  return (1.0 * count / (_pulses_per_kwh));
}
