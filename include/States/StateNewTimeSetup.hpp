#ifndef STATE_NEW_TIME_SETUP_HPP
#define STATE_NEW_TIME_SETUP_HPP

#include "StateBase.hpp"
#include <Arduino.h>

class StateNewTimeSetup : public StateBase
{
public:
    static StateBase *getInstance();

    StateNewTimeSetup();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

protected:
    static uint8_t m_Hours;
    static uint8_t m_Minutes;

private:
    virtual void enter();
    virtual void exit();

    static StateNewTimeSetup m_Instance;
};

#endif