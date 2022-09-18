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
char ssid[] = "1234";
char pass[] = "Silva!081102";

BlynkTimer timer;
// light
BH1750 lightMeter;
float lightIntensity;

// define
int switchInput;

// laser => KY-008
uint8_t laserPin = D5;

void sendSensor()
{
  // read light value
  lightIntensity = lightMeter.readLightLevel();
  Serial.println(lightIntensity);

  // push light value to blynk chart
  Blynk.virtualWrite(V2, lightIntensity);

  // Email
  if (lightIntensity < 300)
  {
    Blynk.logEvent("warning_security_breached", "We have detect unsual behavior around your trip wire!");
  }
};

void laserControl()
{
  digitalWrite(laserPin, (switchInput == 1) ? HIGH : LOW);
}

void buzzer()
{
  if (lightIntensity > 500 && switchInput == 1)
  {
    Serial.println(1);
    delay(100);
  }
  else
  {
    Serial.println(0);
  }
  delay(100);
}

// Blink
BLYNK_WRITE(V0)
{
  switchInput = param.asInt();
  Blynk.virtualWrite(V1, switchInput);
}
void setup()
{
  Serial.begin(9600);
  timer.setInterval(2500L, sendSensor);
  Blynk.begin(auth, ssid, pass);
  Wire.begin();
  lightMeter.begin();
  // laser
  pinMode(laserPin, OUTPUT);
  Serial.println(F("Tripwire Begin!"));
}

void loop()
{
  Blynk.run();
  timer.run();
  laserControl();
  buzzer();
}
