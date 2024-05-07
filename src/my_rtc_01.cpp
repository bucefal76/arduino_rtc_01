#include <LiquidCrystal.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <vector>

#include "KeyboardController.hpp"
#include "ModuleConfig.hpp"
#include "ModuleController.hpp"
#include "Views/MenuView.hpp"
#include "Views/TimeView.hpp"
#include "Views/TimeSetupView.hpp"
#include "Views/ConfirmationView.hpp"
#include "Views/DateSetupView.hpp"

/*
  This code uses an Arduino UNO board, RTC DS1302, and a Standard 16x2 LCD to create a real-time clock.
  To understand the code, it is important to consider two aspects: the View-Controller architectural pattern and the State Machine design pattern.

  The View-Controller is responsible for presenting different information on the screen through separate sets of class views.
  The Controller, on the other hand, manages the device's behavior through its state machine states.
*/

#define USE_SERIAL

#define DAT_IO 9
#define CLK 10
#define RST_CE 8

ThreeWire myWire(DAT_IO, CLK, RST_CE);
RtcDS1302<ThreeWire> rtc(myWire);
std::vector<Thread *> threads;

void setupThreads();
void initalizeRct();
void printDateTime(const RtcDateTime &dt);

//////////////////////////////////////////////////////////////////////////////
/// @brief Setup function, fired only once!
//////////////////////////////////////////////////////////////////////////////
void setup()
{
#ifdef USE_SERIAL
  Serial.begin(9600);
  Serial.print(F("----------------STARTING!!!-----------------"));
  Serial.print(F("compiled: "));
  Serial.print(F(__DATE__));
  Serial.println(F(__TIME__));
#endif

  initalizeRct();

  setupThreads();
}

//////////////////////////////////////////////////////////////////////////////
/// @brief Main program loop.
//////////////////////////////////////////////////////////////////////////////
void loop()
{
  /*
    The Thread library is utilized to simulate time-sharing on a processor,
    similar to what occurs on an operating system. However, this is only an approximation of such behavior,
    as the Thread library does not employ a timer to prompt the task scheduler.
    Instead, it simply keeps track of the number of milliseconds since the last thread activity and executes a thread task when the time comes.
    It's important to note that the loop() function does not control the flow or application logic. All of that occurs within the Thread on Run().
  */

  for (std::vector<Thread *>::iterator it = threads.begin(); it != threads.end(); it++)
  {
    Thread *thread = *it;
    if (nullptr != thread)
    {
      if (thread->shouldRun())
      {
        thread->run();
      }
    }
  }
}

void setupThreads()
{
  LiquidCrystal *lcd = new LiquidCrystal(RS_IO_LINE, EN_IO_LINE, D4_IO_LINE, D5_IO_LINE, D6_IO_LINE, D7_IO_LINE);
  if (nullptr != lcd)
  {
    lcd->begin(LCD_MAX_COLS, LCD_MAX_ROWS);
  }

  // Now is a time to create and connect basic functional blocks of the source codes. First, views:
  if (nullptr != TimeView::getInstance())
  {
    TimeView::getInstance()->setLcd(lcd);
    TimeView::getInstance()->setRtc(&rtc);
  }

  threads.push_back(TimeView::getInstance());
  threads.push_back(MenuView::getInstance());
  threads.push_back(TimeSetupView::getInstance());
  threads.push_back(ConfirmationView::getInstance());
  threads.push_back(DateSetupView::getInstance());

  // Then the keyboard controller...
  threads.push_back(KeyboardController::getInstance());

  // And then the application controller.
  threads.push_back(ModuleController::getInstance());
  // Now created modules are injected to the application controller (dependency injection).

  if (nullptr != ModuleController::getInstance())
  {
    ModuleController::getInstance()->setKeyboardController(KeyboardController::getInstance());
    ModuleController::getInstance()->setViews(TimeView::getInstance(),
                                              MenuView::getInstance(),
                                              MenuView::getInstance(),
                                              TimeSetupView::getInstance(),
                                              TimeSetupView::getInstance(),
                                              ConfirmationView::getInstance(),
                                              DateSetupView::getInstance(),
                                              DateSetupView::getInstance());
    ModuleController::getInstance()->setRtc(&rtc);
  }
}

void initalizeRct()
{
  /*
    Part of the code was found over the Internet with examples of how to use the RtcDS1302 library.
    In this part of the code, some basic settings for the RTC module are done.
  */

  rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
#ifdef USE_SERIAL
  Serial.println();
#endif

  if (!rtc.IsDateTimeValid())
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

#ifdef USE_SERIAL
    Serial.println(F("RTC lost confidence in the DateTime!"));
    Serial.println(F("Setting a new time!"));
#endif
    rtc.SetDateTime(compiled);
  }

  if (rtc.GetIsWriteProtected())
  {
#ifdef USE_SERIAL
    Serial.println(F("RTC was write protected, enabling writing now"));
#endif
    rtc.SetIsWriteProtected(false);
  }

  if (!rtc.GetIsRunning())
  {
#ifdef USE_SERIAL
    Serial.println(F("RTC was not actively running, starting now"));
#endif
    rtc.SetIsRunning(true);
  }

  RtcDateTime now = rtc.GetDateTime();
  if (now < compiled)
  {
#ifdef USE_SERIAL
    Serial.println(F("RTC is older than compile time!  (Updating DateTime)"));
#endif
    rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
#ifdef USE_SERIAL
    Serial.println(F("RTC is newer than compile time. (this is expected)"));
#endif
  }
  else if (now == compiled)
  {
#ifdef USE_SERIAL
    Serial.println(F("RTC is the same as compile time! (not expected but all is fine)"));
#endif
  }
}

#ifdef USE_SERIAL
void printDateTime(const RtcDateTime &dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  Serial.print(datestring);
}
#endif
