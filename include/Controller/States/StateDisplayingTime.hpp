#ifndef STATE_DISPLAYING_TIME_HPP
#define STATE_DISPLAYING_TIME_HPP

#include "StateBase.hpp"

/*
    This state controls the device's behavior when it is displaying time and date.
    This is the most common state for the watch.
*/

class StateDisplayingTime : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    StateDisplayingTime();

    virtual void enter();

    virtual void exit();

    static StateDisplayingTime m_Instance;
};

#endif