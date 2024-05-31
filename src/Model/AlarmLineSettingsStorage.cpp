#include "Model/AlarmLineSettingsStorage.hpp"

#include <Arduino.h>

AlarmLineSettingsStorage::AlarmLineSettingsStorage()
{
    /// temp:
    m_OnTimes[0].consume(AlarmLineFlagTime(1U, 1U));

    m_OnTimes[1].consume(AlarmLineFlagTime(6U, 6U));

    m_OnTimes[2].consume(AlarmLineFlagTime(12U, 12U));

    m_OnTimes[3].consume(AlarmLineFlagTime(18U, 18U));

    m_OffTimes[0].consume(AlarmLineFlagTime(2U, 2U));

    m_OffTimes[1].consume(AlarmLineFlagTime(7U, 7U));

    m_OffTimes[2].consume(AlarmLineFlagTime(13U, 13U));

    m_OffTimes[3].consume(AlarmLineFlagTime(19U, 19U));
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
