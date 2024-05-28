#ifndef MODULE_MODEL_HPP
#define MODULE_MODEL_HPP

#include <Arduino.h>

#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"
#include "DateTime.hpp"
#include "RtcDS1302.h"
#include "RtcDateTime.h"
#include "AlarmLineSettingsStorage.hpp"

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
    virtual bool isAlarmLineArmed(const uint8_t alarmId);
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
};

#endif