#ifndef STATE_DISPLAYING_MENU_SET_ALARMS_HPP
#define STATE_DISPLAYING_MENU_SET_ALARMS_HPP

#include "StateBase.hpp"

/*
    This state controls the device's behavior when it is displaying the "set alarms" submenu.
*/

class StateDisplayingMenuSetAlarms : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    StateDisplayingMenuSetAlarms();

    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetAlarms m_Instance;
};

#endif