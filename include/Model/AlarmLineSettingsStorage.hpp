#ifndef ALARM_LINE_SETTINGS_STORAGE_HPP
#define ALARM_LINE_SETTINGS_STORAGE_HPP

#include <vector>

#include "AlarmLineFlagTime.hpp"
#include "ModuleConfig.hpp"

class AlarmLineSettingsStorage
{
public:
    AlarmLineSettingsStorage();

    bool readFromEeprom();

    AlarmLineFlagTime getOnTimeForCycle(const uint8_t cycle);
    AlarmLineFlagTime getOffTimeForCycle(const uint8_t cycle);

private:
    AlarmLineFlagTime m_OnTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
    AlarmLineFlagTime m_OffTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
};

#endif