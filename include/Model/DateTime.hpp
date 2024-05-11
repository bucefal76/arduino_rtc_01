#ifndef DATTE_TIME_HPP
#define DATTE_TIME_HPP

#include <Arduino.h>

/*
    This class decouples the client code from dependency to the currently used RTC driver implementation.
*/

class RtcDateTime;

class DateTime
{
public:
    explicit DateTime(uint32_t secondsFrom2000 = 0);
    DateTime(uint16_t year,
             uint8_t month,
             uint8_t dayOfMonth,
             uint8_t hour,
             uint8_t minute,
             uint8_t second);
    DateTime();
    /// @brief Returns true if date time is valid
    bool isValid() const;
    /// @brief Returns year value given by the RTC.
    virtual uint16_t getYear() const;
    /// @brief Returns month value given by the RTC.
    virtual uint8_t getMonth() const;
    /// @brief Returns day value given by the RTC.
    virtual uint8_t getDay() const;
    /// @brief Returns hour value given by the RTC.
    virtual uint8_t getHour() const;
    /// @brief Returns minute value given by the RTC.
    virtual uint8_t getMinute() const;
    /// @brief Returns second value given by the RTC.
    virtual uint8_t getSecond() const;

private:
    RtcDateTime *m_pRtcDateTime;
};

#endif