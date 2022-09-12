#define BLYNK_TEMPLATE_ID "TMPLT_M5geTb"
#define BLYNK_DEVICE_NAME "test"
#define BLYNK_AUTH_TOKEN "v-YqxPCpVeOJv9low8SwX19ztuX1K9kt"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// light
#include <BH1750.h>
#include <Wire.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "1234";
char pass[] = "Silva!081102";

BlynkTimer timer;

BH1750 lightMeter;

void sendSensor()
{
  float lux = lightMeter.readLightLevel();
  Serial.println(lux);
  Blynk.virtualWrite(V2, lux);
  delay(1000);
};
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop()
{
  Blynk.run();
  sendSensor();
}