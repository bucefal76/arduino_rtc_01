#ifndef MODULE_MODEL_STATE_IF_HPP
#define MODULE_MODEL_STATE_IF_HPP

#include <Arduino.h>

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
    /// @brief Returns true if alarm selected by alramId is set to be active.
    virtual bool isAlarmActive(const uint8_t alarmId) = 0;
};

#endif