
#include <SoftwareSerial.h>

// Define
int tx = 2;
int rx = 3;
// Message from esp
String espMessage;
// buzzer => KY-012
int buzzerPin = 8;

SoftwareSerial mySerial(3, 2);

void buzzer()
{
  //digitalWrite(buzzerPin, (espMessage == 1) ? LOW : HIGH);
  if (espMessage.equals("1")){
    digitalWrite(buzzerPin, HIGH);
    }
    else if (espMessage.equals("0")) {
  digitalWrite(buzzerPin, LOW);
}

}

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);

  // buzzer
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  espMessage = mySerial.readStringUntil('\r');
  Serial.println(espMessage);
  buzzer();
}
