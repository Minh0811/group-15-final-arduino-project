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

// define
int switchInput;

float lightIntensity;

// laser => KY-008
uint8_t laserPin = D5;

void sendSensor()
{
  lightIntensity = lightMeter.readLightLevel();
   Serial.println(lightIntensity);
  Blynk.virtualWrite(V2, lightIntensity);
  //delay(1000);
    if(lightIntensity > 500){
      Blynk.logEvent("warning_security_breached","We have detect unsual behavior around your trip wire!");
    }
};

void laserControl(){
    digitalWrite(laserPin, (switchInput == 1) ? HIGH : LOW);
  }

void buzzer(){
  if(lightIntensity < 2000 && switchInput == 1){
    Serial.println(1);
    }
    else{
      Serial.println(0);
      }
  }
void email(){
       if(lightIntensity > 500){
     Blynk.email("vokhaiminh0811@gmail.com", "Alert", "Temperature over 28C!");
      Blynk.logEvent("light_alert","Tese");
    }
  }
  
// Blink
BLYNK_WRITE(V0)
{
  switchInput = param.asInt();
  Blynk.virtualWrite(V1, switchInput);
//  Serial.print("Input ");
//  Serial.println(switchInput);
}
void setup()
{
  Serial.begin(9600);
  timer.setInterval(2500L, sendSensor);
  Blynk.begin(auth, ssid, pass);
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);
  lightMeter.begin();

   // laser
    pinMode(laserPin, OUTPUT);

  Serial.println(F("BH1750 Test begin"));
}

void loop()
{
  Blynk.run();
  timer.run();
  //laserControl();
  //buzzer();
}
