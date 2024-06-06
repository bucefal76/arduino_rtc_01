#ifndef MODULE_MODEL_HPP
#define MODULE_MODEL_HPP

#include <Arduino.h>

#include "AlarmLineSettingsStorage.hpp"
#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"
#include "DateTime.hpp"
#include "PCF8574.h"
#include "RtcDS1302.h"
#include "RtcDateTime.h"

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
*/

class ModuleModel : public ModuleModelStateIf, public ModuleModelIf
{
public:
    /// @brief As there is only one RTC hardware module, then
    /// code representation can be only one, we have a singleton in this case.
    /// @return Pointer to the ModuleModel instance.
    static ModuleModel *getInstance();
    /// @brief Says true if date time at RTC is valid. Use this hen call getDateTime().
    virtual bool isDateTimeValid() const;
    /// @brief See ModuleModelStateIf.
    virtual DateTime getDateTime() const;
    /// @brief See ModuleModelStateIf.
    virtual bool isAlarmLineArmed(const uint8_t alarmLineId) const;
    /// @brief See ModuleModelStateIf.
    virtual AlarmLineFlagTime getAlarmLineOnTime(const uint8_t alarmLine, const uint8_t cycle);
    /// @brief See ModuleModelStateIf.
    virtual AlarmLineFlagTime getAlarmLineOffTime(const uint8_t alarmLine, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void setDateTime(const DateTime &dateTime);
    /// @brief See ModuleModelIf.
    virtual bool setAlarmLineOnTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &onTime);
    /// @brief See ModuleModelIf.
    virtual bool setAlarmLineOffTime(const uint8_t alarmLineId, const uint8_t cycle, const TimeInvariant &offTime);
    /// @brief See ModuleModelIf.
    virtual void incrementOnHours(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void decrementOnHours(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void incrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void decrementOnMinutes(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void incrementOffHours(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void decrementOffHours(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void incrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual void decrementOffMinutes(const uint8_t alarmLineId, const uint8_t cycle);
    /// @brief See ModuleModelIf.
    virtual bool saveAlarmLinesSettingsToEEPROM();
    /// @brief See ModuleModelIf.
    virtual uint8_t getIoLineControlWord() const;
    /// @brief See ModuleModelIf.
    virtual void setIoLineControlWord(const uint8_t controlWord);

private:
    ModuleModel();

    void initAlarmSettingsStorage();
    /// @brief Table with the alarm lines settings objects.
    AlarmLineSettingsStorage m_AlarmLinesSettings[ALARMS_NO_OF_LINES];

#ifdef USE_SERIAL
    void
    printDateTime(const RtcDateTime &dt);
#endif

    static ThreeWire m_Wire;
    static RtcDS1302<ThreeWire> m_Rtc;
    static ModuleModel *m_Instance;
    static PCF8574 m_Pfc;
};

#endif