#include <SoftwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>


// Define
int tx = 2;
int rx = 3;

// Message from esp
String espMessage;

// buzzer => KY-012
int buzzerPin = 13;

SoftwareSerial mySerial(3, 2);



Servo myservo;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define Password_Lenght 2 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
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
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10, 11}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad
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
  lcd.begin(16, 2);
  lcd.print(" Arduino Door");
  lcd.setCursor(0, 1);
  lcd.print("--Look project--");
  delay(3000);
  lcd.clear();

  // buzzer
pinMode(buzzerPin, OUTPUT);

}
//////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  //espMessage = mySerial.readStringUntil('\r');

//Serial.println(espMessage);

buzzer();
  if (door == 0)
  {
    customKey = customKeypad.getKey();
    Serial.print(customKey);
    if (customKey == '#')

    {
      lcd.clear();
      ServoClose();
      lcd.print("  Door is close");
      Serial.print("  Door is close");
      delay(3000);
      door = 1;
    }
  }
//////////////////////////////////////////////////////////////////////////////////////

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}

void ServoOpen()
{
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 180; pos += 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password");
  Serial.print(" Enter Password");
  customKey = customKeypad.getKey();
  Serial.print(customKey);
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
      ServoOpen();
      lcd.print("  Door is Open");
       Serial.print("  Door is Open");
      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("  Wrong Password");
            Serial.print("  Wrong Password");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}
void buzzer()

{

//bool sadf = espMessage.equals(1);
//Serial.println(sadf);
int one = 1;
int isTrue = espMessage.toInt();
Serial.println(isTrue);
if (isTrue == one){

digitalWrite(buzzerPin, HIGH);

}

else if (espMessage == espMessage.equals(0)) {

digitalWrite(buzzerPin, LOW);

}

  

}
