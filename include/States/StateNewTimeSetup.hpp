#ifndef STATE_DNEW_TIME_SETUP_HPP
#define STATE_DNEW_TIME_SETUP_HPP

#include "StateBase.hpp"

class StateNewTimeSetup : public StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static StateBase *getInstance();

private:
    virtual void enter();

    virtual void exit();

    static StateNewTimeSetup m_Instance;
};

#endif