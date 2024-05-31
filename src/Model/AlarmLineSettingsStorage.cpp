#include "Model/AlarmLineSettingsStorage.hpp"

#include <Arduino.h>
#include <EEPROM.h>

#include "Model/AlarmLineFlagTime.hpp"
#include "ModuleConfig.hpp"

#define EEPROM_BASE_ADDRESS 0x0001U
#define EEPROM_ALARM_LINE_SIZE (2 * (sizeof(AlarmLineFlagTime) * ALARMS_NO_OF_CYCLES_PER_LINE))

AlarmLineSettingsStorage::AlarmLineSettingsStorage()
{
    ///
}

bool AlarmLineSettingsStorage::readFromEEPROM(const uint8_t alarmLineId)
{
    uint16_t address = EEPROM_BASE_ADDRESS + (alarmLineId * EEPROM_ALARM_LINE_SIZE);

    for (uint8_t it = 0; it < ALARMS_NO_OF_CYCLES_PER_LINE; it++)
    {
        const uint8_t hours = EEPROM.read(address);
        address++;
        const uint8_t minutes = EEPROM.read(address);
        address++;
        m_OnTimes[it].consume(AlarmLineFlagTime(hours, minutes));
    }

    for (uint8_t it = 0; it < ALARMS_NO_OF_CYCLES_PER_LINE; it++)
    {
        const uint8_t hours = EEPROM.read(address);
        address++;
        const uint8_t minutes = EEPROM.read(address);
        address++;
        m_OffTimes[it].consume(AlarmLineFlagTime(hours, minutes));
    }

    return true;
}

bool AlarmLineSettingsStorage::saveToEEPROM(const uint8_t alarmLineId)
{
    uint16_t address = EEPROM_BASE_ADDRESS + (alarmLineId * EEPROM_ALARM_LINE_SIZE);

    for (uint8_t it = 0; it < ALARMS_NO_OF_CYCLES_PER_LINE; it++)
    {
        EEPROM.update(address, m_OnTimes[it].getHours());
        address++;
        EEPROM.update(address, m_OnTimes[it].getMinutes());
        address++;
    }

    for (uint8_t it = 0; it < ALARMS_NO_OF_CYCLES_PER_LINE; it++)
    {
        EEPROM.update(address, m_OffTimes[it].getHours());
        address++;
        EEPROM.update(address, m_OffTimes[it].getMinutes());
        address++;
    }

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
