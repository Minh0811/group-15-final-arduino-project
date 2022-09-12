
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