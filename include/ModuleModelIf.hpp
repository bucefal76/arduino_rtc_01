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

    virtual bool addAlarmLineCycle(const uint8_t alarmLineId, TimeInvariant &onTime, const TimeInvariant &offTime) = 0;
};

#endif