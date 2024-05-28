#include "Model/AlarmLineSettingsStorage.hpp"

#include <Arduino.h>

AlarmLineSettingsStorage::AlarmLineSettingsStorage()
{
    /// temp:
    m_OnTimes[0].m_Hours = 1U;
    m_OnTimes[0].m_Minutes = 1U;

    m_OnTimes[1].m_Hours = 6U;
    m_OnTimes[1].m_Minutes = 6U;

    m_OnTimes[2].m_Hours = 10U;
    m_OnTimes[2].m_Minutes = 10U;

    m_OnTimes[3].m_Hours = 12U;
    m_OnTimes[3].m_Minutes = 12U;

    m_OffTimes[0].m_Hours = 2U;
    m_OffTimes[0].m_Minutes = 2U;

    m_OffTimes[1].m_Hours = 7U;
    m_OffTimes[1].m_Minutes = 7U;

    m_OffTimes[2].m_Hours = 11U;
    m_OffTimes[2].m_Minutes = 11U;

    m_OffTimes[3].m_Hours = 13U;
    m_OffTimes[3].m_Minutes = 13U;
}

bool AlarmLineSettingsStorage::readFromEEPROM(const uint8_t alarmLineId)
{
    return true;
}

bool AlarmLineSettingsStorage::saveToEEPROM(const uint8_t alarmLineId)
{
    return true;
}

TimeInvariant AlarmLineSettingsStorage::getOnTimeForCycle(const uint8_t cycle)
{
    if (cycle < ALARMS_NO_OF_CYCLES_PER_LINE)
    {
        return m_OnTimes[cycle];
    }
    else
    {
        return TimeInvariant();
    }
}

TimeInvariant AlarmLineSettingsStorage::getOffTimeForCycle(const uint8_t cycle)
{
    if (cycle < ALARMS_NO_OF_CYCLES_PER_LINE)
    {
        return m_OffTimes[cycle];
    }
    else
    {
        return TimeInvariant();
    }
}

bool AlarmLineSettingsStorage::setOnTimeForCycle(const TimeInvariant onTime, const uint8_t cycle)
{
    m_OnTimes[cycle] = onTime;

    return true;
}

bool AlarmLineSettingsStorage::setOffTimeForCycle(const TimeInvariant offTime, const uint8_t cycle)
{
    m_OffTimes[cycle] = offTime;

    return true;
}

void AlarmLineSettingsStorage::incrementOnHours(const uint8_t cycle)
{
    m_OnTimes[cycle].incrementHours();
}

void AlarmLineSettingsStorage::decrementOnHours(const uint8_t cycle)
{
    m_OnTimes[cycle].decrementHours();
}

void AlarmLineSettingsStorage::incrementOnMinutes(const uint8_t cycle)
{
    m_OnTimes[cycle].incrementMinutes();
}

void AlarmLineSettingsStorage::decrementOnMinutes(const uint8_t cycle)
{
    m_OnTimes[cycle].decrementMinutes();
}

void AlarmLineSettingsStorage::incrementOffHours(const uint8_t cycle)
{
    m_OffTimes[cycle].incrementHours();
}

void AlarmLineSettingsStorage::decrementOffHours(const uint8_t cycle)
{
    m_OffTimes[cycle].decrementHours();
}

void AlarmLineSettingsStorage::incrementOffMinutes(const uint8_t cycle)
{
    m_OffTimes[cycle].incrementMinutes();
}

void AlarmLineSettingsStorage::decrementOffMinutes(const uint8_t cycle)
{
    m_OffTimes[cycle].decrementMinutes();
}
