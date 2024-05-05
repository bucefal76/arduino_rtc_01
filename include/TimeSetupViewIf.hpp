#ifndef TIME_SETUP_VIEW_IF_HPP
#define TIME_SETUP_VIEW_IF_HPP

#include <Arduino.h>

/*
    Interfaces declares methods required by the view used to set up the time by the operator.
    These methods are not standard ViewIf things, so they require their interface by the SOLID principles.
*/

class TimeSetupViewIf
{
public:
    /// @brief See setState.
    enum TimeSetupViewState
    {
        SETUP_HOURS,
        SETUP_MINUTES,
        SETUP_DONE
    };

    /// @brief Time setup requires modifying display behavior.
    /// For example, setting hours shall be different visually from setting minutes.
    //  This method allows for tuning view behavior.
    /// @param state
    virtual void setState(TimeSetupViewState state) = 0;
    /// @brief Get the curretnt view state, see setState.
    /// @return
    virtual TimeSetupViewState getState() const = 0;
    /// @brief  Set a required hour to display.
    /// @param hours
    virtual void putHours(const uint8_t hours) = 0;
    /// @brief  Set a required minute to display.
    /// @param minutes
    virtual void putMinutes(const uint8_t minutes) = 0;
};

#endif