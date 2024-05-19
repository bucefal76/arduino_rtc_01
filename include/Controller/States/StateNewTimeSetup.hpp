#ifndef STATE_NEW_TIME_SETUP_HPP
#define STATE_NEW_TIME_SETUP_HPP

#include "StateBase.hpp"
#include <Arduino.h>

/*
    This state controls the device behavior when it allows the to set operator a new time.
*/

class StateNewTimeSetup : public StateBase
{
public:
    static StateBase *getInstance();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

protected:
    StateNewTimeSetup();

    static uint8_t m_Hours;
    static uint8_t m_Minutes;

private:
    virtual void enter();
    virtual void exit();

    ViewTimeSetupIf *getMyExtendedView() const;

    static StateNewTimeSetup m_Instance;
};

#endif