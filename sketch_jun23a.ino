#define BLYNK_TEMPLATE_ID "TMPL6Hj-TgYgK"
#define BLYNK_TEMPLATE_NAME "LAMPU GEDUNG"
#define BLYNK_AUTH_TOKEN "4H8zMr6JfSS2jS6aYeKyHq3XjnFospxv"


#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "pai";
char pass[] = "123456789";

#define LED_BUILTIN_ESP32 2

BlynkTimer timer;

// Menerima data dari Switch Blynk pada V0
BLYNK_WRITE(V0)
{
  int switchLED = param.asInt();

  digitalWrite(LED_BUILTIN_ESP32, switchLED);

  Serial.print("Status Lampu: ");
  if (switchLED)
    Serial.println("ON");
  else
    Serial.println("OFF");
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN_ESP32, OUTPUT);
  digitalWrite(LED_BUILTIN_ESP32, LOW);

  Serial.println("Menghubungkan ke Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Terhubung!");
}

void loop()
{
  Blynk.run();
  timer.run();
}