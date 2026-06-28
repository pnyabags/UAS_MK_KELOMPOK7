#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

//=========================
// WiFi
//=========================
const char* ssid = "mi 10T";
const char* password = "solderpanas";

//=========================
// HiveMQ Cloud
//=========================
const char* mqtt_server = "40b58b887c7945d58ff8d5f7d1bc611a.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

// GANTI DENGAN USERNAME & PASSWORD
const char* mqtt_user = "lampuajaib";
const char* mqtt_pass = "Lampuajaib1";

//=========================
// Relay
//=========================
#define RELAY_PIN 27

WiFiClientSecure espClient;
PubSubClient client(espClient);

//=====================================================
// Callback MQTT
//=====================================================

void callback(char* topic, byte* payload, unsigned int length)
{
  String message = "";

  for (int i = 0; i < length; i++)
    message += (char)payload[i];

  Serial.print("Topic : ");
  Serial.println(topic);

  Serial.print("Message : ");
  Serial.println(message);

  if (message == "ON")
  {
    digitalWrite(RELAY_PIN, LOW);      // Active LOW
    client.publish("lampu/status", "ON");
  }

  else if (message == "OFF")
  {
    digitalWrite(RELAY_PIN, HIGH);
    client.publish("lampu/status", "OFF");
  }
}

//=====================================================
// Connect WiFi
//=====================================================

void setup_wifi()
{
  delay(100);

  Serial.println();
  Serial.print("Connecting WiFi ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("========================");
  Serial.println("WiFi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println("========================");
}

//=====================================================
// MQTT Reconnect
//=====================================================

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting MQTT...");

    if (client.connect("ESP32Client", mqtt_user, mqtt_pass))
    {
      Serial.println(" Connected");

      client.subscribe("lampu/control");

      client.publish("lampu/status", "ESP32 Online");
    }
    else
    {
      Serial.print(" Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retry in 5 sec");

      delay(5000);
    }
  }
}

//=====================================================

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF
  digitalWrite(RELAY_PIN, HIGH);

  setup_wifi();

  // Untuk HiveMQ Cloud
  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);

  client.setCallback(callback);
}

//=====================================================

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();
}