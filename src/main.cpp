#include <Arduino.h>

/* 1s fo each measurement */
const int sample_interval = 1000;

unsigned int sample;

void setup() { Serial.begin(115200); }

void loop() {
  unsigned long sample_interval_start = millis();
  unsigned int peak_to_peak = 0;
  unsigned int max_signal = 0;
  unsigned int min_signal = 1024;

  while (millis() - sample_interval_start < sample_interval) {
    /* sample analog value read on A0 */
    sample = analogRead(A0);

    if (sample < min_signal) {
      if (sample > max_signal) {
        /* max_signal goes from 0 -> sample */
        max_signal = sample;
      } else if (sample < min_signal) {
        min_signal = sample;
      }
    }
  }

  /* peak to peak amplitude */
  peak_to_peak = max_signal - min_signal;

  double volts = (peak_to_peak * 5.0) / 1024.0;

  Serial.print("Max signal: ");
  Serial.println(max_signal);

  Serial.print("Min signal: ");
  Serial.println(min_signal);

  Serial.print("Volts: ");
  Serial.println(volts);
  Serial.println();

  delay(1000);
}