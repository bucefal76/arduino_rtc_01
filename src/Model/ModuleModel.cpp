#include "Model/ModuleModel.hpp"
#include "RtcDS1302.h"
#include "ModuleConfig.hpp"

ThreeWire ModuleModel::m_Wire(DAT_IO, CLK, RST_CE);
RtcDS1302<ThreeWire> ModuleModel::m_Rtc(m_Wire);
ModuleModel *ModuleModel::m_Instance = nullptr;

ModuleModel *ModuleModel::getInstance()
{
    if (nullptr == m_Instance)
    {
        m_Instance = new ModuleModel();
    }

    return m_Instance;
}

ModuleModel::ModuleModel()
{
    /*
      Part of the code was found over the Internet with examples of how to use the RtcDS1302 library.
      In this part of the code, some basic settings for the RTC module are done.
    */

    m_Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
#ifdef USE_SERIAL
    printDateTime(compiled);
    Serial.println();
#endif

    if (!m_Rtc.IsDateTimeValid())
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

#ifdef USE_SERIAL
        Serial.println(F("RTC lost confidence in the DateTime!"));
        Serial.println(F("Setting a new time!"));
#endif
        m_Rtc.SetDateTime(compiled);
    }

    if (m_Rtc.GetIsWriteProtected())
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC was write protected, enabling writing now"));
#endif
        m_Rtc.SetIsWriteProtected(false);
    }

    if (!m_Rtc.GetIsRunning())
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC was not running, starting now"));
#endif
        m_Rtc.SetIsRunning(true);
    }

    RtcDateTime now = m_Rtc.GetDateTime();
    if (now < compiled)
    {
#ifdef USE_SERIAL
        Serial.println(F("RTC is older than compile time!  (Updating DateTime)"));
#endif
        m_Rtc.SetDateTime(compiled);
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

    initAlarmSettingsStorage();
}

bool ModuleModel::isDateTimeValid() const
{
    return m_Rtc.IsDateTimeValid();
}

DateTime ModuleModel::getDateTime() const
{
    RtcDateTime dateTime = m_Rtc.GetDateTime();

    return DateTime(dateTime.Year(), dateTime.Month(), dateTime.Day(), dateTime.Hour(), dateTime.Minute(), dateTime.Second(), dateTime.IsValid());
}

void ModuleModel::setDateTime(const DateTime &dateTime)
{
    RtcDateTime rctDateTime(dateTime.getYear(), dateTime.getMonth(), dateTime.getDay(), dateTime.getHour(), dateTime.getMinute(), dateTime.getSecond());

    m_Rtc.SetDateTime(rctDateTime);
}

bool ModuleModel::isAlarmLineArmed(const uint8_t alarmLineId) const
{
    return m_AlarmLinesSettings[alarmLineId].isAlarmLineArmed();
}

AlarmLineFlagTime ModuleModel::getAlarmLineOnTime(const uint8_t alarmLine, const uint8_t cycle)
{
    if (alarmLine < ALARMS_NO_OF_LINES)
    {
        return m_AlarmLinesSettings[alarmLine].getOnTimeForCycle(cycle).getAlarmLineFlagTime();
    }
    else
    {
        return AlarmLineFlagTime();
    }
}

AlarmLineFlagTime ModuleModel::getAlarmLineOffTime(const uint8_t alarmLine, const uint8_t cycle)
{
    if (alarmLine < ALARMS_NO_OF_LINES)
    {
        return m_AlarmLinesSettings[alarmLine].getOffTimeForCycle(cycle).getAlarmLineFlagTime();
    }
    else
    {
        return AlarmLineFlagTime();
    }
}

bool ModuleModel::setAlarmLineOnTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &onTime)
{
    return m_AlarmLinesSettings[alarmLineId].setOnTimeForCycle(onTime, cycle);
}

bool ModuleModel::setAlarmLineOffTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &offTime)
{
    return m_AlarmLinesSettings[alarmLineId].setOffTimeForCycle(offTime, cycle);
}

void ModuleModel::initAlarmSettingsStorage()
{
    for (uint8_t alarmLineIt = 0; alarmLineIt < ALARMS_NO_OF_LINES; alarmLineIt++)
    {
        m_AlarmLinesSettings[alarmLineIt].readFromEEPROM(alarmLineIt);
    }
}

void ModuleModel::incrementOnHours(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].incrementOnHours(cycle);
}

void ModuleModel::decrementOnHours(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].decrementOnHours(cycle);
}

void ModuleModel::incrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].incrementOnMinutes(cycle);
}

void ModuleModel::decrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].decrementOnMinutes(cycle);
}

void ModuleModel::incrementOffHours(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].incrementOffHours(cycle);
}

void ModuleModel::decrementOffHours(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].decrementOffHours(cycle);
}

void ModuleModel::incrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].incrementOffMinutes(cycle);
}

void ModuleModel::decrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle)
{
    m_AlarmLinesSettings[alarmLineId].decrementOffMinutes(cycle);
}

bool ModuleModel::saveAlarmLinesSettingsToEEPROM()
{
    for (uint8_t it = 0; it < ALARMS_NO_OF_LINES; it++)
    {
        if (false == m_AlarmLinesSettings[it].saveToEEPROM(it))
        {
            return false;
        }
    }

    return true;
}

#ifdef USE_SERIAL
void ModuleModel::printDateTime(const RtcDateTime &dt)
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