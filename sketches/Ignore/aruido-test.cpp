
#include <SoftwareSerial.h>
#include <Keypad.h>            // the library for the 4x4 keypad
#include <LiquidCrystal_I2C.h> // the library for the i2c 1602 Serial
#include <Servo.h>             // the library to control the servo motor
// LiquidCrystal_I2C Serial(0x3F,20,4); // gets the Serial
Servo servo;

// Define
int tx = 2;
int rx = 3;
// Message from esp
String espMessage;
// buzzer => KY-012
int buzzerPin = 12;

SoftwareSerial mySerial(3, 2);

#define Password_Length 2                      // the length of the password, if the password is 4 digits long set this to 5
int Position = 0;                              // position of the servo
char Particular[Password_Length];              // the password length
char Specific[Password_Length] = "3";          // the password which is called specific in the code, change this to anything you want with the numbers 0-9 and the letters A-D
byte Particular_Count = 0, Specific_Count = 0; // counts the amount of digits and and checks to see if the password is correct
char Key;
const byte ROWS = 4;      // the amount of rows on the keypad
const byte COLS = 4;      // the amount of columns on the keypad
char keys[ROWS][COLS] = { // sets the rowns and columns
    // sets the keypad digits
    {'1', '2', '3', 'A'},

    {'4', '5', '6', 'B'},

    {'7', '8', '9', 'C'},

    {'*', '0', '#', 'D'}};
bool SmartDoor = true; // the servo
// the pins to plug the keypad into
byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 9, 10};
Keypad myKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // gets the data from the keypad

// locked charcater
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

void buzzer()
{
    // digitalWrite(buzzerPin, (espMessage == 1) ? LOW : HIGH);
    if (espMessage.equals("1"))
    {
        digitalWrite(buzzerPin, HIGH);
    }
    else if (espMessage.equals("0"))
    {
        digitalWrite(buzzerPin, LOW);
    }
}

void setup()
{
    Serial.begin(57600);
    mySerial.begin(9600);

    // buzzer
    pinMode(buzzerPin, OUTPUT);

    servo.attach(11); // attaches the servo to pin 10
    // ServoClose(); // closes the servo when you say this function
    // Serial.begin(9600); // initializes the Serial
    // Serial.backlight(); // turns on the backlight
    // Serial.setCursor(0,0); // sets the cursor on the Serial
    Serial.println("Vector X"); // printlns the text/charater
    // Serial.setCursor(0,1); // sets the cursor on the Serial
    Serial.println("Arduino Lock!!!"); // printlns text
    delay(4000);                       // waits 4 seconds
                                       // Serial.clear(); // clears the Serial diplay
}

void loop()
{
    espMessage = mySerial.readStringUntil('\r');
    Serial.println(espMessage);
    //  buzzer();
    //
    // // Key = myKeypad.getKey();
    // // Serial.println(Key);
    //  if (SmartDoor == 0) // opens the smart door
    //  {
    //    Key = myKeypad.getKey(); // the word key = myKeypad which gets the value
    //
    //    if (Key == '#') // when the '#' key is pressed
    //
    //    {
    //      //erial.clear(); // clears the Serial diplay
    //      ServoClose(); // closes the servo motor
    //    //  Serial.setCursor(2,0); // sets the cursor on the Serial
    //      Serial.println("Door Closed"); // printlns the text to the Serial
    //      //Serial.createChar(0, Locked); // printlns the locked character
    //    //  Serial.setCursor(14,0); // sets the cursor on the Serial
    //      Serial.write(0); // printlns the first character when you are on the door closed page
    //      delay(3000); // waits 3 seconds
    //      SmartDoor = 1; // closes the door
    //    }
    //  }
    //
    //  else Open(); // keeps the door open
    //}
    //
    // void clearData() // clears the data
    //{
    //  while (Particular_Count != 0) // counts the digits pressed
    //  {
    //    Particular[Particular_Count--] = 0; // counts how many digits
    //  }
    //  return; // returns the data
}

void ServoOpen() // opens the servo
{
    for (Position = 180; Position >= 0; Position -= 5)
    {                          // moves from 0 to 180 degrees
        servo.write(Position); // moves to the postion
        delay(15);             // waits 15 milliseconds
    }
}

void ServoClose() // closes the servo
{
    for (Position = 0; Position <= 180; Position += 5)
    {                          // moves from position 0 to 180 degrees
        servo.write(Position); // moves to the position
        delay(15);             // waits 15 milliseconds
    }
}

void Open() // function declarations
{
    // Serial.setCursor(1,0); // sets the cursor on the Serial
    // Serial.println("Enter Password:"); // printlns the text

    Key = myKeypad.getKey(); // gets the keys you press from the keypad
    if (Key)
    {
        Particular[Particular_Count] = Key;
        // Serial.setCursor(Particular_Count, 1); // sets the cursor on the Serial
        Serial.println(Key); // printlns '*' instead of the password
        Particular_Count++;  // counts the length of the password
    }

    if (Particular_Count == Password_Length - 1) // gets the length of the password
    {
        if (!strcmp(Particular, Specific)) // counts the length and checks to see if the password is correct
        {
            // Serial.clear();
            ServoOpen(); // moves the servo 180 degrees
                         //  Serial.setCursor(2,0); // sets the cursor on the Serial
            Serial.println("Door Opened");
            //  Serial.createChar(1, Opened);
            //  Serial.setCursor(14,0); // sets the cursor on the Serial
            Serial.write(1);
            //   Serial.setCursor(0,1); // sets the cursor on the Serial
            Serial.println("Press # to Close");
            SmartDoor = 0;
        }
        else
        {
            // Serial.clear();
            //  Serial.setCursor(0,0); // sets the cursor on the Serial
            Serial.println("Wrong Password"); // printlns the text/character
                                              // Serial.setCursor(0,1);
            Serial.println("Try Again In");
            // Serial.setCursor(13,1);
            Serial.println("04");
            delay(1000);
            //   Serial.setCursor(13,1);
            Serial.println("03");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("02");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("01");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("00");
            delay(1000);
            // Serial.clear();
            SmartDoor = 1; // closes the smart door
        }
        // clearData(); // clears the data
    }
}
#include <SoftwareSerial.h>
#include <Keypad.h>            // the library for the 4x4 keypad
#include <LiquidCrystal_I2C.h> // the library for the i2c 1602 Serial
#include <Servo.h>             // the library to control the servo motor
// LiquidCrystal_I2C Serial(0x3F,20,4); // gets the Serial
Servo servo;

// Define
int tx = 2;
int rx = 3;
// Message from esp
String espMessage;
// buzzer => KY-012
int buzzerPin = 12;

SoftwareSerial mySerial(3, 2);

#define Password_Length 2                      // the length of the password, if the password is 4 digits long set this to 5
int Position = 0;                              // position of the servo
char Particular[Password_Length];              // the password length
char Specific[Password_Length] = "3";          // the password which is called specific in the code, change this to anything you want with the numbers 0-9 and the letters A-D
byte Particular_Count = 0, Specific_Count = 0; // counts the amount of digits and and checks to see if the password is correct
char Key;
const byte ROWS = 4;      // the amount of rows on the keypad
const byte COLS = 4;      // the amount of columns on the keypad
char keys[ROWS][COLS] = { // sets the rowns and columns
    // sets the keypad digits
    {'1', '2', '3', 'A'},

    {'4', '5', '6', 'B'},

    {'7', '8', '9', 'C'},

    {'*', '0', '#', 'D'}};
bool SmartDoor = true; // the servo
// the pins to plug the keypad into
byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 9, 10};
Keypad myKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // gets the data from the keypad

// locked charcater
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

void buzzer()
{
    // digitalWrite(buzzerPin, (espMessage == 1) ? LOW : HIGH);
    if (espMessage.equals("1"))
    {
        digitalWrite(buzzerPin, HIGH);
    }
    else if (espMessage.equals("0"))
    {
        digitalWrite(buzzerPin, LOW);
    }
}

void setup()
{
    Serial.begin(57600);
    mySerial.begin(9600);

    // buzzer
    pinMode(buzzerPin, OUTPUT);

    servo.attach(11); // attaches the servo to pin 10
    // ServoClose(); // closes the servo when you say this function
    // Serial.begin(9600); // initializes the Serial
    // Serial.backlight(); // turns on the backlight
    // Serial.setCursor(0,0); // sets the cursor on the Serial
    Serial.println("Vector X"); // printlns the text/charater
    // Serial.setCursor(0,1); // sets the cursor on the Serial
    Serial.println("Arduino Lock!!!"); // printlns text
    delay(4000);                       // waits 4 seconds
                                       // Serial.clear(); // clears the Serial diplay
}

void loop()
{
    espMessage = mySerial.readStringUntil('\r');
    Serial.println(espMessage);
    //  buzzer();
    //
    // // Key = myKeypad.getKey();
    // // Serial.println(Key);
    //  if (SmartDoor == 0) // opens the smart door
    //  {
    //    Key = myKeypad.getKey(); // the word key = myKeypad which gets the value
    //
    //    if (Key == '#') // when the '#' key is pressed
    //
    //    {
    //      //erial.clear(); // clears the Serial diplay
    //      ServoClose(); // closes the servo motor
    //    //  Serial.setCursor(2,0); // sets the cursor on the Serial
    //      Serial.println("Door Closed"); // printlns the text to the Serial
    //      //Serial.createChar(0, Locked); // printlns the locked character
    //    //  Serial.setCursor(14,0); // sets the cursor on the Serial
    //      Serial.write(0); // printlns the first character when you are on the door closed page
    //      delay(3000); // waits 3 seconds
    //      SmartDoor = 1; // closes the door
    //    }
    //  }
    //
    //  else Open(); // keeps the door open
    //}
    //
    // void clearData() // clears the data
    //{
    //  while (Particular_Count != 0) // counts the digits pressed
    //  {
    //    Particular[Particular_Count--] = 0; // counts how many digits
    //  }
    //  return; // returns the data
}

void ServoOpen() // opens the servo
{
    for (Position = 180; Position >= 0; Position -= 5)
    {                          // moves from 0 to 180 degrees
        servo.write(Position); // moves to the postion
        delay(15);             // waits 15 milliseconds
    }
}

void ServoClose() // closes the servo
{
    for (Position = 0; Position <= 180; Position += 5)
    {                          // moves from position 0 to 180 degrees
        servo.write(Position); // moves to the position
        delay(15);             // waits 15 milliseconds
    }
}

void Open() // function declarations
{
    // Serial.setCursor(1,0); // sets the cursor on the Serial
    // Serial.println("Enter Password:"); // printlns the text

    Key = myKeypad.getKey(); // gets the keys you press from the keypad
    if (Key)
    {
        Particular[Particular_Count] = Key;
        // Serial.setCursor(Particular_Count, 1); // sets the cursor on the Serial
        Serial.println(Key); // printlns '*' instead of the password
        Particular_Count++;  // counts the length of the password
    }

    if (Particular_Count == Password_Length - 1) // gets the length of the password
    {
        if (!strcmp(Particular, Specific)) // counts the length and checks to see if the password is correct
        {
            // Serial.clear();
            ServoOpen(); // moves the servo 180 degrees
                         //  Serial.setCursor(2,0); // sets the cursor on the Serial
            Serial.println("Door Opened");
            //  Serial.createChar(1, Opened);
            //  Serial.setCursor(14,0); // sets the cursor on the Serial
            Serial.write(1);
            //   Serial.setCursor(0,1); // sets the cursor on the Serial
            Serial.println("Press # to Close");
            SmartDoor = 0;
        }
        else
        {
            // Serial.clear();
            //  Serial.setCursor(0,0); // sets the cursor on the Serial
            Serial.println("Wrong Password"); // printlns the text/character
                                              // Serial.setCursor(0,1);
            Serial.println("Try Again In");
            // Serial.setCursor(13,1);
            Serial.println("04");
            delay(1000);
            //   Serial.setCursor(13,1);
            Serial.println("03");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("02");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("01");
            delay(1000);
            // Serial.setCursor(13,1);
            Serial.println("00");
            delay(1000);
            // Serial.clear();
            SmartDoor = 1; // closes the smart door
        }
        // clearData(); // clears the data
    }
}