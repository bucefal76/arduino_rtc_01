#ifndef TIME_SETUP_VIEW_IF_HPP
#define TIME_SETUP_VIEW_IF_HPP

#include <Arduino.h>

class TimeSetupViewIf
{
public:
    enum TimeSetupViewState
    {
        SETUP_HOURS,
        SETUP_MINUTES,
        SETUP_DONE
    };

    virtual void setState(TimeSetupViewState state) = 0;
    virtual TimeSetupViewState getState() const = 0;
    virtual void putHours(const uint8_t hours) = 0;
    virtual void putMinutes(const uint8_t minutes) = 0;
};

#endif