#include "config.h"
#include "impulse_counter.h"
#include "Meter.h"
#include "mqtt.h"


//RunningAverage impulse_running_average(1000);
Meter meter(PULSES_PER_KWH);

const int impulsePin = A0;
boolean impulseDetected = false;
int threshold = 60;

long interval = 30UL * 1000UL;
unsigned long previousMillis = 0;
char *mqttOutTopic = "sensors/nrg2/out";

void setup_impulse_counter() {  
//  impulse_running_average.clear();
}

void impulse_counter_task() {
  int illuminanceValue = analogRead(impulsePin);

  Serial.println(illuminanceValue);
  

//  impulse_running_average.addValue((float) illuminanceValue);
//  int threshold = (int) ((impulse_running_average.getMinInBuffer() + impulse_running_average.getMaxInBuffer()) / 2);

  delay(5);

  if ((illuminanceValue > threshold) & (impulseDetected == false)) {
    impulseDetected = true;
    delay(5);
  }

  if ((illuminanceValue < threshold) & (impulseDetected == true)) {
    impulseDetected = false;
    meter.pulse();
    Serial.println("pulse");
    delay(5);
  }

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    DynamicJsonDocument doc(1024);

    doc["energy"] = meter.get_elapsed_energy();
    doc["power"] = meter.get_power();

    char output[256];
    serializeJson(doc, output);
    publish_message(mqttOutTopic, output);
  }  
}
