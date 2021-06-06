#include "mqtt.h"
#include "wifi.h"
#include "config.h"

void setup_mqtt() {
  mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt_client.setKeepAlive(120);
}

void reconnect_mqtt() {
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt_client.connect(NODE_NAME, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("mqtt connected");

    } else {
      WiFi.printDiag(Serial);
      Serial.print("mqtt failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void mqtt_task() {
  // check connection
  if (wifi_connected()) {
    if (!mqtt_client.connected()) {
      reconnect_mqtt();
    }

    mqtt_client.loop();
  }
}

void publish_message(char* topic, char* payload) {
  mqtt_client.publish(topic, payload);
}
