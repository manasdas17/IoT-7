#include <float.h>
#include <limits.h>√
#include "Measurements.h"
#include "Arduino.h"

measurements::measurements():
  m_nb_of_mea_stored(0),
  m_current_measure(0),
  m_temp_sum(0),
  m_hum_sum(0),
  m_pres_sum(0) {
    for (uint16_t i = 0; i < N; i++) {
      m_mea_avg[i].temperature = FLT_MAX;
      m_mea_avg[i].humidity = FLT_MAX;
      m_mea_avg[i].pressure = INT_MAX;

      m_mea_min[i].temperature = FLT_MAX;
      m_mea_min[i].humidity = FLT_MAX;
      m_mea_min[i].pressure = INT_MAX;

      m_mea_max[i].temperature = FLT_MIN;
      m_mea_max[i].humidity = FLT_MIN;
      m_mea_max[i].pressure = INT_MIN;

      m_start_hour = millis();
      m_end_hour = m_start_hour + HOUR;
    }
}

void measurements::new_measurement(measure_value p_measure, unsigned long p_timestamp) {
  if (p_timestamp <= m_end_hour) {
    if (p_measure.temperature < m_mea_min[m_current_measure].temperature)
      m_mea_min[m_current_measure].temperature = p_measure.temperature;
    if (p_measure.humidity < m_mea_min[m_current_measure].humidity)
      m_mea_min[m_current_measure].humidity = p_measure.humidity;
    if (p_measure.pressure < m_mea_min[m_current_measure].pressure)
      m_mea_min[m_current_measure].pressure = p_measure.pressure;

    if (p_measure.temperature > m_mea_max[m_current_measure].temperature)
      m_mea_max[m_current_measure].temperature = p_measure.temperature;
    if (p_measure.humidity > m_mea_max[m_current_measure].humidity)
      m_mea_max[m_current_measure].humidity = p_measure.humidity;
    if (p_measure.pressure > m_mea_max[m_current_measure].pressure)
      m_mea_max[m_current_measure].pressure = p_measure.pressure;

    m_nb_of_mea_stored++;
    m_temp_sum += p_measure.temperature;
    m_hum_sum += p_measure.humidity;
    m_pres_sum += p_measure.pressure;
  } else {
    m_mea_avg[m_current_measure].temperature = m_temp_sum / m_nb_of_mea_stored;
    m_mea_avg[m_current_measure].humidity = m_hum_sum / m_nb_of_mea_stored;
    m_mea_avg[m_current_measure].pressure = m_pres_sum / m_nb_of_mea_stored;

    m_current_measure = (m_current_measure + 1) % N;
    m_start_hour = m_end_hour;
    m_end_hour = millis() + HOUR;
    m_nb_of_mea_stored = 0;
  }
}