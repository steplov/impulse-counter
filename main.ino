#include "led.h"
#include "wifi.h"
#include "mqtt.h"
#include "impulse_counter.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  setup_led();
  setup_wifi();
  setup_mqtt();  
//  setup_ota();
  setup_impulse_counter();

  print_wifi_details();
}

void loop() {
  wifi_task();
  mqtt_task();
  impulse_counter_task();
}
