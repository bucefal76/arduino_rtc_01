#include "Model/DateTime.hpp"
#include "RtcDS1302.h"
#include "SerialPrintAssert.h"

DateTime::DateTime(uint16_t year,
                   uint8_t month,
                   uint8_t dayOfMonth,
                   uint8_t hour,
                   uint8_t minute,
                   uint8_t second,
                   bool isValid)
    : m_Year(year),
      m_Month(month),
      m_Day(dayOfMonth),
      m_Hour(hour),
      m_Minute(minute),
      m_Second(second),
      m_IsValid(isValid)
{
}

DateTime::DateTime()
    : m_Year(0U),
      m_Month(0U),
      m_Day(0U),
      m_Hour(0U),
      m_Minute(0U),
      m_Second(0U),
      m_IsValid(0U)
{
}

bool DateTime::isValid() const
{
    return m_IsValid;
}

uint16_t DateTime::getYear() const
{
    return m_Year;
}

uint8_t DateTime::getMonth() const
{
    return m_Month;
}

uint8_t DateTime::getDay() const
{
    return m_Day;
}

uint8_t DateTime::getHour() const
{
    return m_Hour;
}

uint8_t DateTime::getMinute() const
{
    return m_Minute;
}

uint8_t DateTime::getSecond() const
{
    return m_Second;
}
