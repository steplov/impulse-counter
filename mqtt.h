#include <PubSubClient.h>
#include "wifi.h"

#ifndef MQTT_H
#define MQTT_H

static PubSubClient mqtt_client(espClient);

void setup_mqtt();
void reconnect_mqtt();
void mqtt_task();
void publish_message(char* topic, char* payload);
#endif
