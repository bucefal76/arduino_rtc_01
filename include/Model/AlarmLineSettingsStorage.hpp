#ifndef ALARM_LINE_SETTINGS_STORAGE_HPP
#define ALARM_LINE_SETTINGS_STORAGE_HPP

#include <vector>

#include "AlarmLineFlagTime.hpp"
#include "TimeInvariant.hpp"
#include "ModuleConfig.hpp"

class AlarmLineSettingsStorage
{
public:
    AlarmLineSettingsStorage();

    bool readFromEEPROM(const uint8_t alarmLineId);
    bool saveToEEPROM(const uint8_t alarmLineId);

    TimeInvariant getOnTimeForCycle(const uint8_t cycle);
    TimeInvariant getOffTimeForCycle(const uint8_t cycle);
    bool setOnTimeForCycle(const TimeInvariant onTile, const uint8_t cycle);
    bool setOffTimeForCycle(const TimeInvariant offTile, const uint8_t cycle);
    void incrementOnHours(const uint8_t cycle);
    void decrementOnHours(const uint8_t cycle);
    void incrementOnMinutes(const uint8_t cycle);
    void decrementOnMinutes(const uint8_t cycle);
    void incrementOffHours(const uint8_t cycle);
    void decrementOffHours(const uint8_t cycle);
    void incrementOffMinutes(const uint8_t cycle);
    void decrementOffMinutes(const uint8_t cycle);

private:
    TimeInvariant m_OnTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
    TimeInvariant m_OffTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
};

#endif