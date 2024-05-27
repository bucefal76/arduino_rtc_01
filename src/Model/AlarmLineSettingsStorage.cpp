#include "Model/AlarmLineSettingsStorage.hpp"

AlarmLineSettingsStorage::AlarmLineSettingsStorage()
{
}

bool AlarmLineSettingsStorage::readFromEeprom()
{
    return true;
}

AlarmLineFlagTime AlarmLineSettingsStorage::getOnTimeForCycle(const uint8_t cycle)
{
    if (cycle < ALARMS_NO_OF_CYCLES_PER_LINE)
    {
        return m_OnTimes[cycle];
    }
    else
    {
        return AlarmLineFlagTime();
    }
}

AlarmLineFlagTime AlarmLineSettingsStorage::getOffTimeForCycle(const uint8_t cycle)
{
    if (cycle < ALARMS_NO_OF_CYCLES_PER_LINE)
    {
        return m_OffTimes[cycle];
    }
    else
    {
        return AlarmLineFlagTime();
    }
}