#ifndef STATE_DISPLAYING_TIME_HPP
#define STATE_DISPLAYING_TIME_HPP

#include "StateBase.hpp"

class StateDisplayingTime: public StateBase
{
public:
    
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase* getInstance();

private:

    virtual void enter(){};

    virtual void exit();

    static StateDisplayingTime m_Instance;
};

#endif