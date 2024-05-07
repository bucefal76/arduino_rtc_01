#ifndef STATE_DISPLAYING_MENU_SET_DATE_HPP
#define STATE_DISPLAYING_MENU_SET_DATE_HPP

#include "StateBase.hpp"

/*
    This state controls the device's behavior when it is displaying the "set date" submenu.
*/

class StateDisplayingMenuSetDate : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetDate m_Instance;
};

#endif