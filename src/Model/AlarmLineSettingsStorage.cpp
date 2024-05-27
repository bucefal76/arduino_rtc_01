#include "Model/AlarmLineSettingsStorage.hpp"

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