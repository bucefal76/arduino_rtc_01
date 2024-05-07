#ifndef STATE_DISPLAYING_MENU_SET_TIME_HPP
#define STATE_DISPLAYING_MENU_SET_TIME_HPP

#include "StateBase.hpp"

/*
    This state controls the device's behavior when it is displaying the "set time" submenu.
*/

class StateDisplayingMenuSetTime : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetTime m_Instance;
};

#endif