#include <LiquidCrystal.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>

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

void setup()
{
#ifdef USE_SERIAL
  Serial.begin(9600);
  Serial.print(F("----------------STARTING!!!-----------------"));
  Serial.print(F("compiled: "));
  Serial.print(F(__DATE__));
  Serial.println(F(__TIME__));
#endif

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

  LiquidCrystal *lcd = new LiquidCrystal(RS_IO_LINE, EN_IO_LINE, D4_IO_LINE, D5_IO_LINE, D6_IO_LINE, D7_IO_LINE);
  if (nullptr != lcd)
  {
    lcd->begin(LCD_MAX_COLS, LCD_MAX_ROWS);
  }

  // Now is a time to create and connect basic functional blocks of the source codes. First, views:
  TimeView *timeView = TimeView::getInstance();
  if (nullptr != timeView)
  {
    timeView->setLcd(lcd);
    timeView->setRtc(&rtc);
  }
  MenuView *menuView = MenuView::getInstance();
  TimeSetupView *timeSetupView = TimeSetupView::getInstance();
  ConfirmationView *confirmationView = ConfirmationView::getInstance();
  DateSetupView *dataSetupView = DateSetupView::getInstance();
  // Then the keyboard controller...

  KeyboardController *keyboardController = KeyboardController::getInstance();

  // And then the application controller.
  ModuleController *moduleController = ModuleController::getInstance();
  // Now created modules are injected to the application controller (dependency injection).

  moduleController->setKeyboardController(keyboardController);
  moduleController->setViews(timeView, menuView, menuView, timeSetupView, timeSetupView, confirmationView, dataSetupView);
  moduleController->setRtc(&rtc);
}

void loop()
{
  /*
    The Thread library is utilized to simulate time-sharing on a processor,
    similar to what occurs on an operating system. However, this is only an approximation of such behavior,
    as the Thread library does not employ a timer to prompt the task scheduler.
    Instead, it simply keeps track of the number of milliseconds since the last thread activity and executes a thread task when the time comes.
    It's important to note that the loop() function does not control the flow or application logic. All of that occurs within the Thread on Run().
  */

  // Now give a time to the views:

  TimeView *timeView = TimeView::getInstance();
  if (nullptr != timeView)
  {
    if (timeView->shouldRun())
    {
      timeView->run();
    }
  }

  MenuView *menuView = MenuView::getInstance();
  if (nullptr != menuView)
  {
    if (menuView->shouldRun())
    {
      menuView->run();
    }
  }

  TimeSetupView *timeSetupView = TimeSetupView::getInstance();
  if (nullptr != timeSetupView)
  {
    if (timeSetupView->shouldRun())
    {
      timeSetupView->run();
    }
  }

  DateSetupView *dataSetupView = DateSetupView::getInstance();
  if (nullptr != dataSetupView)
  {
    if (dataSetupView->shouldRun())
    {
      dataSetupView->run();
    }
  }

  ConfirmationView *confirmationView = ConfirmationView::getInstance();
  if (nullptr != confirmationView)
  {
    if (confirmationView->shouldRun())
    {
      confirmationView->run();
    }
  }

  // Now give a time to the keyboard controller to get any input:
  KeyboardController *keyboardController = KeyboardController::getInstance();
  if (nullptr != keyboardController)
  {
    if (keyboardController->shouldRun())
    {
      keyboardController->run();
    }
  }

  // Now process the input with application controller:
  ModuleController *moduleController = ModuleController::getInstance();
  if (nullptr != moduleController)
  {
    if (moduleController->shouldRun())
    {
      moduleController->run();
    }
  }
}
