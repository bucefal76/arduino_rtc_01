#ifndef STATE_DISPLAYING_MENU_SET_EXIT_HPP
#define STATE_DISPLAYING_MENU_SET_EXIT_HPP

#include "StateBase.hpp"

class StateDisplayingMenuSetExit : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    virtual void enter();

    virtual void exit();

    static StateDisplayingMenuSetExit m_Instance;
};

#endif