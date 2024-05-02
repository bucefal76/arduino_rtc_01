#ifndef TIME_SETUP_VIEW_IF_HPP
#define TIME_SETUP_VIEW_IF_HPP

#include <Arduino.h>

class TimeSetupViewIf
{
public:
    virtual void putHours(const uint8_t hour) = 0;
    virtual void putMinutes(const uint8_t hour) = 0;
};

#endif