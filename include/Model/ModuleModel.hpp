#ifndef MODULE_MODEL_HPP
#define MODULE_MODEL_HPP

#include <Arduino.h>

#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "DateTime.hpp"
#include "RtcDS1302.h"
#include "RtcDateTime.h"

class ModuleModel : public ModuleModelIf
{
public:
    /// @brief As there is only one RTC hardware module, then
    /// code representation can be only one, we have a singleton in this case.
    /// @return Pointer to the ModuleModel instance.
    static ModuleModel *getInstance();
    /// @brief
    /// @return
    virtual bool isDateTimeValid() const;
    /// @brief
    /// @return
    virtual DateTime getDateTime() const;
    /// @brief
    /// @param dt
    virtual void setDateTime(const DateTime &dateTime);

    // temp solution
    RtcDS1302<ThreeWire> *getRtc()
    {
        return &m_Rtc;
    }

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