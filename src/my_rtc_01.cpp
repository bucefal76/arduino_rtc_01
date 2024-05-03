#include <LiquidCrystal.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>

#include "KeyboardController.hpp"
#include "ModuleConfig.hpp"
#include "ModuleController.hpp"
#include "Views/MenuView.hpp"
#include "Views/TimeView.hpp"
#include "Views/TimeSetupView.hpp"

#define USE_SERIAL

/*
#define DAT_IO D4
#define CLK D5
#define RST_CE D3
*/

#define DAT_IO 9
#define CLK 10
#define RST_CE 8

KeyboardController keyboard;

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

  LiquidCrystal *lcd = new LiquidCrystal(RS, EN, D4, D5, D6, D7);
  if (nullptr != lcd)
  {
    lcd->begin(LCD_MAX_COLS, LCD_MAX_ROWS);
  }

  TimeView *timeView = TimeView::getInstance();
  if (nullptr != timeView)
  {
    timeView->setLcd(lcd);
    timeView->setRtc(&rtc);
  }
  MenuView *menuView = MenuView::getInstance();
  TimeSetupView *timeSetupView = TimeSetupView::getInstance();

  KeyboardController *keyboardController = KeyboardController::getInstance();

  ModuleController *moduleController = ModuleController::getInstance();

  moduleController->setKeyboardController(keyboardController);
  moduleController->setViews(timeView, menuView, menuView, timeSetupView, timeSetupView);
  moduleController->setRtc(&rtc);
}

void loop()
{

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

  KeyboardController *keyboardController = KeyboardController::getInstance();
  if (nullptr != keyboardController)
  {
    if (keyboardController->shouldRun())
    {
      keyboardController->run();
    }
  }

  ModuleController *moduleController = ModuleController::getInstance();
  if (nullptr != moduleController)
  {
    if (moduleController->shouldRun())
    {
      moduleController->run();
    }
  }
}
