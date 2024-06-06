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
    /// @brief Set new value of ON time for alarm line for selected ON/OFF cycle.
    /// @param alarmLineId Alarm line id.
    /// @param cycle Cycle time to select.
    /// @param onTime Time to set alarm line to ON.
    /// @return True if success.
    virtual bool setAlarmLineOnTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &onTime) = 0;
    /// @brief Set new value of OFF time for alarm line for selected ON/OFF cycle.
    /// @param alarmLineId Alarm line id.
    /// @param cycle Cycle time to select.
    /// @param onTime Time to set alarm line to OFF.
    /// @return True if success.
    virtual bool setAlarmLineOffTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &offTime) = 0;
    /// @brief Increment alarm line ON time by one hour for selected cycle.
    virtual void incrementOnHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Decrement alarm line ON time by one hour for selected cycle.
    virtual void decrementOnHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Increment alarm line ON time by one minute for selected cycle.
    virtual void incrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Decrement alarm line ON time by one minute for selected cycle.
    virtual void decrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Increment alarm line OFF time by one hour for selected cycle.
    virtual void incrementOffHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Decrement alarm line OFF time by one hour for selected cycle.
    virtual void decrementOffHours(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Increment alarm line OFF time by one minute for selected cycle.
    virtual void incrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Decrement alarm line OFF time by one minute for selected cycle.
    virtual void decrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle) = 0;
    /// @brief Save current settings of the alarm lines ON and OFF cycles to the EEPROM.
    /// @return True if save succeeded.
    virtual bool saveAlarmLinesSettingsToEEPROM() = 0;
    /// @brief Get 8 bit value that represents IO lines state.
    virtual uint8_t getIoLineControlWord() const = 0;
    /// @brief Set 8 bit value that control the IO lines state.
    /// @param controlWord New value of the IO lines.
    virtual void setIoLineControlWord(const uint8_t controlWord) = 0;
};

#endif