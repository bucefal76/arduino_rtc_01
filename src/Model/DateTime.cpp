#include "Model/DateTime.hpp"
#include "assert.h"
#include "RtcDS1302.h"

DateTime::DateTime(uint32_t secondsFrom2000)
{
    m_pRtcDateTime = new RtcDateTime(secondsFrom2000);
    assert(nullptr != m_pRtcDateTime);
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
    assert(nullptr != m_pRtcDateTime);
}

DateTime::DateTime()
{
    m_pRtcDateTime = new RtcDateTime(__DATE__, __TIME__);
}

bool DateTime::isValid() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->IsValid();
}

uint16_t DateTime::getYear() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Year();
}

uint8_t DateTime::getMonth() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Month();
}

uint8_t DateTime::getDay() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Day();
}

uint8_t DateTime::getHour() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Hour();
}

uint8_t DateTime::getMinute() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Minute();
}

uint8_t DateTime::getSecond() const
{
    assert(nullptr != m_pRtcDateTime);
    return m_pRtcDateTime->Second();
}
