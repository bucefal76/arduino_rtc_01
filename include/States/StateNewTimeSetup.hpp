#ifndef STATE_DNEW_TIME_SETUP_HPP
#define STATE_DNEW_TIME_SETUP_HPP

#include "StateBase.hpp"
#include <Arduino.h>

class StateNewTimeSetup : public StateBase
{
public:
    static StateBase *getInstance();

    StateNewTimeSetup();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

private:
    virtual void
    enter();
    virtual void exit();

    uint8_t m_Hours;
    uint8_t m_Minutes;

    static StateNewTimeSetup m_Instance;
};

#endif