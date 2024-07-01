#ifndef MODULE_MODEL_STATE_IF_HPP
#define MODULE_MODEL_STATE_IF_HPP

#include <Arduino.h>
#include "Model/AlarmLineFlagTime.hpp"

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
    The idea is to have no dependencies in the rest of the code to the RCT-specific code.

    This interface allows to get the Model state only. Can be used by any component.
*/

class DateTime;

class ModuleModelStateIf
{
public:
    /// @brief Returns true if date time at RTC is valid.
    virtual bool isDateTimeValid() const = 0;
    /// @brief Returns DateTime structure
    virtual DateTime getDateTime() const = 0;
    /// @brief Returns true if alarm selected by alarmLineId is armed to be active witch some cycle.
    virtual bool isAlarmLineArmed(const uint8_t alarmLineId) = 0;
    /// @brief Return value of alarm On time for selected alarm line and selected cycle.
    virtual AlarmLineFlagTime getAlarmLineOnTime(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Return value of alarm Off time for selected alarm line and selected cycle.
    virtual AlarmLineFlagTime getAlarmLineOffTime(const uint8_t alarmLineId, const uint8_t cycle) = 0;
};

#endif