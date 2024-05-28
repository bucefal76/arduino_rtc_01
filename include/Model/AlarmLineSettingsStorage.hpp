#ifndef ALARM_LINE_SETTINGS_STORAGE_HPP
#define ALARM_LINE_SETTINGS_STORAGE_HPP

#include <vector>

#include "AlarmLineFlagTime.hpp"
#include "ModuleConfig.hpp"

class AlarmLineSettingsStorage
{
public:
    AlarmLineSettingsStorage();

    bool readFromEEPROM(const uint8_t alarmLineId);
    bool saveToEEPROM(const uint8_t alarmLineId);

    AlarmLineFlagTime getOnTimeForCycle(const uint8_t cycle);
    AlarmLineFlagTime getOffTimeForCycle(const uint8_t cycle);
    bool setOnTimeForCycle(const AlarmLineFlagTime onTile, const uint8_t cycle);
    bool setOffTimeForCycle(const AlarmLineFlagTime offTile, const uint8_t cycle);

private:
    AlarmLineFlagTime m_OnTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
    AlarmLineFlagTime m_OffTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
};

#endif