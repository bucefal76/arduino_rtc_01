#ifndef DATE_SETUP_VIEW_IF_HPP
#define DATE_SETUP_VIEW_IF_HPP

#include <Arduino.h>

class DateSetupViewIf
{
public:
    enum DateSetupViewState
    {
        SETUP_DAYS,
        SETUP_MONTH,
        SETUP_YEAS,
        SETUP_DONE
    };

    virtual void setState(const DateSetupViewState state) = 0;

    virtual DateSetupViewState getState() const = 0;

    virtual void putYear(const uint16_t year) = 0;

    virtual void putMonth(const uint8_t month) = 0;

    virtual void putDay(const uint8_t day) = 0;
};

#endif