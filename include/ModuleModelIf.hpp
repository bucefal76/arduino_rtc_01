#ifndef MODULE_MODEL_IF_HPP
#define MODULE_MODEL_IF_HPP

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
*/

class DateTime;

class ModuleModelIf
{
public:
    /// @brief
    /// @return
    virtual bool isDateTimeValid() const = 0;
    /// @brief
    /// @return
    virtual DateTime getDateTime() const = 0;
    /// @brief
    /// @param dt
    virtual void setDateTime(const DateTime &dateTime) = 0;
};

#endif