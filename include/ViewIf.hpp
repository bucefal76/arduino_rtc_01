#ifndef VIEW_IF_HPP
#define VIEW_IF_HPP

#include <Arduino.h>

class LiquidCrystal;

/*
    This is an interface for basic functionality for all views used in this clock application.
    The idea is the ViewIf defines the interface for the View component in the Controller - View pair.
*/

class ViewIf
{
public:
    /// @brief Returns the view ID.
    virtual uint8_t getViewId() const = 0;
    /// @brief Views require a pointer to the LCD driver to display view content.
    /// @param pLcd
    virtual void setLcd(LiquidCrystal *pLcd) = 0;
    /// @brief  A method is called each time when view is enabled by the Controller state machine.
    virtual void enable() = 0;
    /// @brief A method is called each time when view is disabled by the Controller state machine.
    virtual void disable() = 0;
};

#endif