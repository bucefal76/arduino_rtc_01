#ifndef STATE_NEW_DATE_SETUP_HPP
#define STATE_NEW_DATE_SETUP_HPP

#include "StateBase.hpp"
#include <Arduino.h>

/*
    This state controls the device behavior when it allows the to set operator a new date.
*/

class StateNewDateSetup : public StateBase
{
public:
    static StateBase *getInstance();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

protected:
    StateNewDateSetup();

    static uint16_t m_Year;
    static uint8_t m_Month;
    static uint8_t m_Day;

private:
    virtual void enter();
    virtual void exit();

    void updateViewData() const;
    uint8_t getNumberOfDays(const uint8_t month, const uint16_t year) const;

    static StateNewDateSetup m_Instance;
};

#endif