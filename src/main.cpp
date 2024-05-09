#include <Arduino.h>
#include "ModuleConfig.hpp"
#include "ModuleApplication.hpp"
#include "ModuleApplicationBuilder.hpp"

/*
  This code uses an Arduino UNO board, RTC DS1302, and a Standard 16x2 LCD to create a real-time clock.
  To understand the code, it is important to consider two aspects: the View-Controller architectural pattern and the State Machine design pattern.

  The View-Controller is responsible for presenting different information on the screen through separate sets of class views.
  The Controller, on the other hand, manages the device's behavior through its state machine states.
*/

//////////////////////////////////////////////////////////////////////////////
// Global objects:
ModuleApplication gApplication;
//////////////////////////////////////////////////////////////////////////////

void printDateTime(const RtcDateTime &dt);

//////////////////////////////////////////////////////////////////////////////
/// @brief Setup function, fired only once!
//////////////////////////////////////////////////////////////////////////////
void setup()
{
#ifdef USE_SERIAL
  Serial.begin(9600);
  Serial.print(F("Starting module, compiled time and date is: "));
  Serial.print(F(__DATE__));
  Serial.println(F(__TIME__));
#endif

  ModuleApplicationBuilder gApplicationBuilder;
  gApplicationBuilder.buildApplication(gApplication);
}

//////////////////////////////////////////////////////////////////////////////
/// @brief Main program loop.
//////////////////////////////////////////////////////////////////////////////
void loop()
{
  gApplication.runThreads();
}
