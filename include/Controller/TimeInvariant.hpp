#ifndef ALARM_TIME_HPP
#define ALARM_TIME_HPP

#include "ModuleConfig.hpp"

struct TimeInvariant
{
public:
    uint8_t m_Hours;
    uint8_t m_Minutes;

    TimeInvariant()
        : m_Hours(0U), m_Minutes(0U)
    {
    }

    TimeInvariant(const uint8_t hour, const uint8_t minute)
        : m_Hours(hour), m_Minutes(minute)
    {
    }

    uint8_t getHours()
    {
        return m_Hours;
    }

    uint8_t getMinutes()
    {
        return m_Minutes;
    }

    void incrementHours()
    {
        m_Hours++;
        if (m_Hours > HOURS_MAX_VALUE)
        {
            m_Hours = HOURS_MIN_VALUE;
        }
    }

    void decrementHours()
    {
        if (m_Hours > HOURS_MIN_VALUE)
        {
            m_Hours--;
        }
        else if (m_Hours == HOURS_MIN_VALUE)
        {
            m_Hours = HOURS_MAX_VALUE;
        }
    }

    void incrementMinutes()
    {
        m_Minutes++;
        if (m_Minutes > MINUTES_MAX_VALUE)
        {
            m_Minutes = MINUTES_MIN_VALUE;
        }
    }

    void decrementMinutes()
    {
        if (m_Minutes > MINUTES_MIN_VALUE)
        {
            m_Minutes--;
        }
        else if (m_Minutes == MINUTES_MIN_VALUE)
        {
            m_Minutes = MINUTES_MAX_VALUE;
        }
    }
};

#endif