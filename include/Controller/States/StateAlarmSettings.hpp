#ifndef STATE_ALARM_SETTINGS_HPP
#define STATE_ALARM_SETTINGS_HPP

#include "StateBase.hpp"
#include "Controller/TimeInvariant.hpp"

class StateAlarmSettings : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    StateAlarmSettings();

    virtual void enter();

    virtual void exit();

    static StateAlarmSettings m_Instance;

    TimeInvariant m_OnTime;
    TimeInvariant m_OffTime;
};

#endif
