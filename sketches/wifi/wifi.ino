#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
#include <Wire.h>
#include <BH1750.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "uktf"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = // 60 bytes
    {255, 1, 0, 0, 0, 53, 0, 16, 67, 1, 2, 1, 17, 43, 27, 13, 37, 26, 31, 31,
     79, 78, 0, 79, 70, 70, 0, 129, 0, 4, 19, 56, 5, 94, 80, 114, 101, 115, 115, 32,
     116, 111, 32, 100, 105, 115, 97, 98, 108, 101, 32, 116, 114, 105, 112, 119, 105, 114, 101, 0};

// this structure defines all the variables and events of your control interface
struct
{

  // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF

  // other variable
  uint8_t connect_flag; // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 7

// light sensor => BH1750)
#define ADDR 0b0100011
BH1750 GY30;
float lux;

// buzzer => KY-012
int buzzerPin = 8;
void setup()
{
  RemoteXY_Init();

  pinMode(PIN_SWITCH_1, OUTPUT);

  // TODO you setup code
  // light sensor
  Serial.begin(115200);                           // launch the serial monitor
  Wire.begin();                                   // Initialize the I2C bus for use by the BH1750 library
  GY30.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2); // Initialize the sensor object
  Serial.println("Flux Workshop Example");

  // buzzer
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  RemoteXY_Handler();

  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1 == 0) ? LOW : HIGH);

  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay()
  // lightSensor();
  // buzzer();
  lux = GY30.readLightLevel();
  if (lux < 2000 && RemoteXY.switch_1 == 1)
  {
      digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
}
void lightSensor()
{
  lux = GY30.readLightLevel();                      // read the light level from the sensor and store it in a variable
  Serial.println((String) "Light: " + lux + " lx"); // print the data to the serial monitor
                                                    // delay(100);                                       // Pause for a second before repeating the sensor poll
}
void buzzer()
{
  if (lux > 500000)
  {
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      delay(500);
    }
  }
}
