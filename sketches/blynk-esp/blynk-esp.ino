/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - NodeMCU board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLT_M5geTb"
#define BLYNK_DEVICE_NAME "test"
#define BLYNK_AUTH_TOKEN "v-YqxPCpVeOJv9low8SwX19ztuX1K9kt"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// light
#include <BH1750.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "1234";
char pass[] = "Silva!081102";

// light
BH1750 GY30;
float lux;

BLYNK_WRITE(V0)
{
  digitalWrite(D0, param.asInt());
}

void setup()
{
  pinMode(D0, OUTPUT);
  // Debug console
  Serial.begin(115200);
  // light
  GY30.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  // Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  lux = 3;
  if (lux > 2)
  {
    Blynk.email("vokhaiminh0811@gmail.com", "sensor data", "light is above 2");
  }
}

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
}

void loop()
{
  String msg = mySerial.readStringUntil('\r');
  Serial.println(msg);
}