#include <Wire.h>   //dunno wat is dis
#include <Servo.h>  //servo motor
#include <Adafruit_MLX90614.h>  //temperature sensor

Servo myservo;
// HC-SR04 (UltraSonic)
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 // attach pin D3 Arduino to pin Trig of HC-SR04
long duration;    // variable for the duration of sound wave travel
int distance;     // variable for the distance measurement
int pos = 0;
#define SOUND_VELOCITY 0.034

void setup()
{
    Serial.begin(9600);
    // HC-SR04
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
    myservo.attach(10); // access input pin #10
}

void ultraSonic()
{
    digitalWrite(trigPin, LOW); // Clears the trigPin
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds

    distance = duration * SOUND_VELOCITY / 2; // Calculate the distance
}

// Openlid done
// weight: wait for ESP2866 to be done

void loop()
{
  ultraSonic_openlid(); // 2 ultrasonic sensors: openlid + weight
  if (distance <= 5) {
    myservo.write(90);
    delay(15000);
  } else {
    myservo.write(0);
    // delay(15);
  }
    delay(500);
}
