#include "Model/DateTime.hpp"
#include "RtcDS1302.h"
#include "SerialPrintAssert.h"

DateTime::DateTime(uint32_t secondsFrom2000)
{
    m_pRtcDateTime = new RtcDateTime(secondsFrom2000);
    RUNTIME_PTR_CHECK(m_pRtcDateTime);
}

DateTime::DateTime(uint16_t year,
                   uint8_t month,
                   uint8_t dayOfMonth,
                   uint8_t hour,
                   uint8_t minute,
                   uint8_t second)
    : m_pRtcDateTime(nullptr)
{
    m_pRtcDateTime = new RtcDateTime(year, month, dayOfMonth, hour, minute, second);
    RUNTIME_PTR_CHECK(m_pRtcDateTime);
}

DateTime::DateTime()
{
    m_pRtcDateTime = new RtcDateTime(__DATE__, __TIME__);
    RUNTIME_PTR_CHECK(m_pRtcDateTime);
}

bool DateTime::isValid() const
{
    RUNTIME_PTR_CHECK(m_pRtcDateTime);
    return m_pRtcDateTime->IsValid();
}

uint16_t DateTime::getYear() const
{
    return m_pRtcDateTime->Year();
}

uint8_t DateTime::getMonth() const
{
    return m_pRtcDateTime->Month();
}

uint8_t DateTime::getDay() const
{
    return m_pRtcDateTime->Day();
}

uint8_t DateTime::getHour() const
{
    return m_pRtcDateTime->Hour();
}

uint8_t DateTime::getMinute() const
{
    return m_pRtcDateTime->Minute();
}

uint8_t DateTime::getSecond() const
{
    return m_pRtcDateTime->Second();
}
