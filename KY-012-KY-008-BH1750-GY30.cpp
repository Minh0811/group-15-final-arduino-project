#include <Wire.h>
#include <BH1750.h>

BH1750 GY30;

// laser => KY-008
int laserPin = 12;

// light sensor => BH1750)
#define ADDR 0b0100011
float lux;
// buzzer => KY-012
int buzzerPin = 8;

void setup()
{
    // laser
    pinMode(laserPin, OUTPUT);

    // light sensor
    Serial.begin(9600);                             // launch the serial monitor
    Wire.begin();                                   // Initialize the I2C bus for use by the BH1750 library
    GY30.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2); // Initialize the sensor object
    Serial.println("Flux Workshop Example");

    // buzzer
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
    laser();
    lightSensor();
    buzzer();
}

void laser()
{
    digitalWrite(laserPin, HIGH);
}

void lightSensor()
{
    lux = GY30.readLightLevel();                      // read the light level from the sensor and store it in a variable
    Serial.println((String) "Light: " + lux + " lx"); // print the data to the serial monitor
    delay(100);                                       // Pause for a second before repeating the sensor poll
}
void buzzer()
{
    if (lux < 50)
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