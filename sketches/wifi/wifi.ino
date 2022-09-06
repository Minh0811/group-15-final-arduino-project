// https://www.youtube.com/watch?v=6-RXqFS_UtU

// https://www.youtube.com/watch?v=YLKEZtLhfZo
// https://blynk.io/


//wifi

// https://www.youtube.com/watch?v=2cjufbgOBYo&list=PL9UWJqkOPUWQj76q1ycopIgc4SwHzlGQ6&index=4&t=185s
// code
/*
   -- New project --

   This source code of graphical user interface
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "uktf"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = // 36 bytes
    {255, 2, 0, 0, 0, 29, 0, 16, 31, 1, 2, 0, 35, 58, 22, 11, 2, 26, 31, 31,
     79, 78, 0, 79, 70, 70, 0, 1, 0, 13, 51, 12, 12, 2, 31, 0};

// this structure defines all the variables and events of your control interface
struct
{

    // input variables
    uint8_t switch_1; // =1 if switch ON and =0 if OFF
    uint8_t button_1; // =1 if button pressed, else =0

    // other variable
    uint8_t connect_flag; // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 13
#define PIN_BUTTON_1 12

void setup()
{
    RemoteXY_Init();

    pinMode(PIN_SWITCH_1, OUTPUT);
    pinMode(PIN_BUTTON_1, OUTPUT);

    // TODO you setup code
}

void loop()
{
    RemoteXY_Handler();

    digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1 == 0) ? LOW : HIGH);
    digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1 == 0) ? LOW : HIGH);

    // TODO you loop code
    // use the RemoteXY structure for data transfer
    // do not call delay()
}
