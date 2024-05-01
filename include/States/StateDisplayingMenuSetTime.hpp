#ifndef STATE_DISPLAYING_MENU_SET_TIME_HPP
#define STATE_DISPLAYING_MENU_SET_TIME_HPP

#include "StateBase.hpp"

class StateDisplayingMenuSetTime: public StateBase
{
public:
    
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase* getInstance();

private:

    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetTime m_Instance;
};

#endif