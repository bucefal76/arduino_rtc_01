#ifndef MODULE_MODEL_HPP
#define MODULE_MODEL_HPP

#include <Arduino.h>

#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "DateTime.hpp"
#include "RtcDS1302.h"
#include "RtcDateTime.h"

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
*/

class ModuleModel : public ModuleModelIf
{
public:
    /// @brief As there is only one RTC hardware module, then
    /// code representation can be only one, we have a singleton in this case.
    /// @return Pointer to the ModuleModel instance.
    static ModuleModel *getInstance();
    /// @brief Says true if date time at RTC is valid.
    virtual bool isDateTimeValid() const;
    /// @brief Returns Date and Time as DateTime struct from the RTC.
    virtual DateTime getDateTime() const;
    /// @brief Sets the new date and time to the RTC.
    virtual void setDateTime(const DateTime &dateTime);

private:
    ModuleModel();

#ifdef USE_SERIAL
    void printDateTime(const RtcDateTime &dt);
#endif

    static ThreeWire m_Wire;
    static RtcDS1302<ThreeWire> m_Rtc;
    static ModuleModel *m_Instance;
};

#endif