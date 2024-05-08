#include "Products/Rtc01/Rtc01ApplicationBuilder.hpp"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>

#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"

#include "KeyboardController.hpp"
#include "ModuleController.hpp"
#include "Views/MenuView.hpp"
#include "Views/TimeView.hpp"
#include "Views/TimeSetupView.hpp"
#include "Views/ConfirmationView.hpp"
#include "Views/DateSetupView.hpp"

ThreeWire myWire(DAT_IO, CLK, RST_CE);
RtcDS1302<ThreeWire> rtc(myWire);

Rtc01ApplicationBuilder::Rtc01ApplicationBuilder()
{
}

void Rtc01ApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    initalizeRct();

    setupThreads(rApplication);
}

void Rtc01ApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
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

    rApplication.addThread(TimeView::getInstance());
    rApplication.addThread(MenuView::getInstance());
    rApplication.addThread(TimeSetupView::getInstance());
    rApplication.addThread(ConfirmationView::getInstance());
    rApplication.addThread(DateSetupView::getInstance());

    // Then the keyboard controller...
    rApplication.addThread(KeyboardController::getInstance());

    // And then the application controller.
    rApplication.addThread(ModuleController::getInstance());
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

void Rtc01ApplicationBuilder::initalizeRct()
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
void Rtc01ApplicationBuilder::printDateTime(const RtcDateTime &dt)
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