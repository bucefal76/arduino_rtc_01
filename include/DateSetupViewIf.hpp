#ifndef DATE_SETUP_VIEW_IF_HPP
#define DATE_SETUP_VIEW_IF_HPP

#include <Arduino.h>
#include "ExtendedViewIf.hpp"

/*
    Interfaces declares methods required by the view used to set up the date by the operator.
    These methods are not standard ViewIf things, so they require their interface by the SOLID principles.
*/

class DateSetupViewIf: public ExtendedViewIf
{
public:
    /// @brief See setState.
    enum DateSetupViewState
    {
        SETUP_YEAR,
        SETUP_MONTH,
        SETUP_DAY,
        SETUP_DONE
    };
    /// @brief Date setup requires modifying display behavior.
    /// For example, setting year shall be different visually from setting month.
    //  This method allows for tuning view behavior.
    virtual void setState(const DateSetupViewState state) = 0;
    /// @brief Returns the current display mode of the DateSetupViewIf.
    virtual DateSetupViewState getState() const = 0;
    /// @brief Sets the year value to display.
    virtual void putYear(const uint16_t year) = 0;
    /// @brief Sets the month value to display.
    virtual void putMonth(const uint8_t month) = 0;
    /// @brief Sets the day value to display.
    virtual void putDay(const uint8_t day) = 0;
};

#endif