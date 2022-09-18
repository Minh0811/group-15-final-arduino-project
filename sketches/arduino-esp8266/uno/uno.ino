#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Servo.h>

// Define
int tx = 2;
int rx = 3;

// Message from esp
String espMessage;

// buzzer => KY-012
int buzzerPin = 13;

SoftwareSerial mySerial(rx, tx);

Servo myservo;

#define Password_Lenght 2 // Give enough room for six chars + NULL char

int pos = 0; // variable to store the servo position

char Data[Password_Lenght];
char Master[Password_Lenght] = "3";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
bool door = true;

byte rowPins[ROWS] = {4, 5, 6, 7};   // connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10, 11}; // connect to the column pinouts of the keypad

Keypad customKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // initialize an instance of class NewKeypad
byte Locked[8] = {
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11011,
    B11011,
    B11111};
// open character
byte Opened[8] = {
    B01110,
    B00001,
    B00001,
    B11111,
    B11011,
    B11011,
    B11011,
    B11111};

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
  myservo.attach(12);
  ServoClose();
  delay(3000);

  // buzzer
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  espMessage = mySerial.readStringUntil('\r');
  Serial.println(espMessage);
  buzzer();

  if (door == 0)
  {
    customKey = customKeypad.getKey();
    Serial.print(customKey);
    if (customKey == '#')

    {
      ServoClose();
      Serial.print("  Door is close");
      delay(3000);
      door = 1;
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////

  else
    Open();
}

void clearData()
{
  while (data_count != 0)
  {                         // This can be used for any array size,
    Data[data_count--] = 0; // clear array for new data
  }
  return;
}

void ServoOpen()
{
  for (pos = 180; pos >= 0; pos -= 5)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 180; pos += 5)
  {                     // goes from 180 degrees to 0 degrees
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
}

void Open()
{
  Serial.print(" Enter Password");
  customKey = customKeypad.getKey();
  Serial.print(customKey);
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    data_count++;                 // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      ServoOpen();
      Serial.print("  Door is Open");
      door = 0;
    }
    else
    {
      Serial.print("  Wrong Password");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}
void buzzer()
{
  if (espMessage.equals("1"))
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else if (espMessage.equals("0"))
  {
    digitalWrite(buzzerPin, LOW);
  }
}
