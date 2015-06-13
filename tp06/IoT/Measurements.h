#pragma once
#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#define N 10
#define HOUR  60*60*1000

#include <stdint.h>
#include <avr/pgmspace.h>

// Temperature, humidity & pressure measurements structure
// float: 4 bytes, uint32_t: 4 bytes -> 12 bytes
typedef struct measure_value {
  float temperature;
  float humidity;
  uint32_t pressure; 
}measure_value;

class measurements {
public:
  measurements(void);

  void new_measurement(measure_value p_measure, unsigned long p_timestamp);
private:
  measure_value m_mea_avg[N] PROGMEM;
  measure_value m_mea_min[N] PROGMEM;
  measure_value m_mea_max[N] PROGMEM;

  uint16_t m_nb_of_mea_stored;
  float m_temp_sum;
  float m_hum_sum;
  unsigned long m_pres_sum;

  unsigned long m_start_hour;
  unsigned long m_end_hour;

  uint16_t m_current_measure;
};
#endif