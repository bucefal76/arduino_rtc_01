#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"

ThreeWire ModuleApplicationBuilder::m_myWire(DAT_IO, CLK, RST_CE);
RtcDS1302<ThreeWire> ModuleApplicationBuilder::m_rtc(m_myWire);

void ModuleApplicationBuilder::initalizeRct()
{
    /*
      Part of the code was found over the Internet with examples of how to use the RtcDS1302 library.
      In this part of the code, some basic settings for the RTC module are done.
    */

    m_rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
#ifdef USE_SERIAL
    Serial.println();
#endif

    if (!m_rtc.IsDateTimeValid())
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

#ifdef USE_SERIAL
        Serial.println(F("RTC lost confidence in the DateTime!"));
        Serial.println(F("Setting a new time!"));
#endif
        m_rtc.SetDateTime(compiled);
    }

    if (m_rtc.GetIsWriteProtected())
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC was write protected, enabling writing now"));
#endif
        m_rtc.SetIsWriteProtected(false);
    }

    if (!m_rtc.GetIsRunning())
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC was not actively running, starting now"));
#endif
        m_rtc.SetIsRunning(true);
    }

    RtcDateTime now = m_rtc.GetDateTime();
    if (now < compiled)
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC is older than compile time!  (Updating DateTime)"));
#endif
        m_rtc.SetDateTime(compiled);
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
void ModuleApplicationBuilder::printDateTime(const RtcDateTime &dt)
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