#ifndef DISPPLAY_ALARMS_STATUS_HPP
#define DISPPLAY_ALARMS_STATUS_HPP

#include "StateBase.hpp"

/*
    This state controls the device's behavior when it is displaying the states of all alarms.
*/

class AlarmsStatusViewIf;

class StateDisplayAlarmsStatus : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    StateDisplayAlarmsStatus();

    virtual void enter();

    virtual void exit();

    AlarmsStatusViewIf *getAlarmsStatusView();

    uint8_t m_AlarmId;

    static StateDisplayAlarmsStatus m_Instance;
};

#endif