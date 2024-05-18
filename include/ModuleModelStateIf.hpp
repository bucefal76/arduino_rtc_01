#ifndef MODULE_MODEL_STATE_IF_HPP
#define MODULE_MODEL_STATE_IF_HPP

#include <Arduino.h>

class DateTime;

class ModuleModelStateIf
{
public:
    /// @brief Returns true if date time at RTC is valid.
    virtual bool isDateTimeValid() const = 0;
    /// @brief Returns DateTime structure
    virtual DateTime getDateTime() const = 0;
    /// @brief
    virtual bool isAlarmActive(const uint8_t alarmId) = 0;
};

#endif