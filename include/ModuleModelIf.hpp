#ifndef MODULE_MODEL_IF_HPP
#define MODULE_MODEL_IF_HPP

#include <Arduino.h>
#include "Model/TimeInvariant.hpp"

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
    The idea is to have no dependencies in the rest of the code to the RCT-specific code.

    This interface allows to change the Model state. Shall be used only by the Controller.
*/

class DateTime;

class ModuleModelIf
{
public:
    /// @brief Set a new date and time on the RCT.
    virtual void setDateTime(const DateTime &dateTime) = 0;

    virtual bool setAlarmLineOnTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &onTime) = 0;

    virtual bool setAlarmLineOffTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &offTime) = 0;

    virtual void incrementOnHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void decrementOnHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void incrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void decrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void incrementOffHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void decrementOffHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void incrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;

    virtual void decrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;
};

#endif