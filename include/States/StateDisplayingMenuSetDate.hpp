#ifndef STATE_DISPLAYING_MENU_SET_DATE_HPP
#define STATE_DISPLAYING_MENU_SET_DATE_HPP

#include "StateBase.hpp"

class StateDisplayingMenuSetDate: public StateBase
{
public:
    
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase* getInstance();

private:

    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetDate m_Instance;
};

#endif