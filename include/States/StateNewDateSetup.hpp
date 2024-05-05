#ifndef STATE_NEW_DATE_SETUP_HPP
#define STATE_NEW_DATE_SETUP_HPP

#include "StateBase.hpp"
#include <Arduino.h>

class StateNewDateSetup : public StateBase
{
public:
    static StateBase *getInstance();

    StateNewDateSetup();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

protected:
    static uint16_t m_Year;
    static uint8_t m_Month;
    static uint8_t m_Day;

private:
    virtual void enter();
    virtual void exit();

    static StateNewDateSetup m_Instance;
};

#endif