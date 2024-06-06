#ifndef ALARM_LINE_SETTINGS_STORAGE_HPP
#define ALARM_LINE_SETTINGS_STORAGE_HPP

#include <vector>

#include "AlarmLineFlagTime.hpp"
#include "TimeInvariant.hpp"
#include "ModuleConfig.hpp"

/*
    Alarm line settings (ON/OFF times) are saved and restored to and from the Atmega EEPROM.
    This class provides the necessary save/restore functionality.
*/

class AlarmLineSettingsStorage
{
public:
    AlarmLineSettingsStorage();
    /// @brief Get alarm line On and OFF times from the  EEPROM
    bool readFromEEPROM(const uint8_t alarmLineId);
    /// @brief Set the alarm line ON and OFF times to the EEPROM.
    bool saveToEEPROM(const uint8_t alarmLineId);
    /// @brief Get On time for selected cycle.
    TimeInvariant getOnTimeForCycle(const uint8_t cycle) const;
    /// @brief Get OFF time for selected cycle.
    TimeInvariant getOffTimeForCycle(const uint8_t cycle) const;
    /// @brief  Set ON time for selected cycle
    /// @param onTime Time to set line High
    /// @param cycle Cycle for time to set
    /// @return Success when new ON time is set.
    bool setOnTimeForCycle(const TimeInvariant onTime, const uint8_t cycle);
    /// @brief  Set OFF time for selected cycle
    /// @param onTime Time to set line High
    /// @param cycle Cycle for time to set
    /// @return Success when new OFF time is set.
    bool setOffTimeForCycle(const TimeInvariant offTile, const uint8_t cycle);
    /// @brief Increment or decrement hours or minutes for selected cycle.
    void incrementOnHours(const uint8_t cycle);
    void decrementOnHours(const uint8_t cycle);
    void incrementOnMinutes(const uint8_t cycle);
    void decrementOnMinutes(const uint8_t cycle);
    void incrementOffHours(const uint8_t cycle);
    void decrementOffHours(const uint8_t cycle);
    void incrementOffMinutes(const uint8_t cycle);
    void decrementOffMinutes(const uint8_t cycle);

    bool isAlarmLineArmed() const;

private:
    TimeInvariant m_OnTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
    TimeInvariant m_OffTimes[ALARMS_NO_OF_CYCLES_PER_LINE];
};

#endif