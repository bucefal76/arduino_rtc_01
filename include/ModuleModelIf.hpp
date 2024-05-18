#ifndef MODULE_MODEL_IF_HPP
#define MODULE_MODEL_IF_HPP

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
    The idea is to have no dependencies in the rest of the code to the RCT-specific code.
*/

class DateTime;

class ModuleModelIf
{
public:
    /// @brief Set a new date and time on the RCT.
    virtual void setDateTime(const DateTime &dateTime) = 0;
};

#endif