#ifndef STATE_NEW_TIME_SETUP_HPP
#define STATE_NEW_TIME_SETUP_HPP

#include <Arduino.h>

#include "StateBase.hpp"
#include "Controller/TimeInvariant.hpp"

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

    static TimeInvariant m_Time;

private:
    virtual void enter();
    virtual void exit();

    ViewTimeSetupIf *getMyExtendedView() const;

    static StateNewTimeSetup m_Instance;
};

#endif