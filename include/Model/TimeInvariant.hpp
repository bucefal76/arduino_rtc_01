#ifndef ALARM_TIME_INVARIANT_HPP
#define ALARM_TIME_INVARIANT_HPP

#include "ModuleConfig.hpp"
#include "Model/AlarmLineFlagTime.hpp"

struct TimeInvariant : protected AlarmLineFlagTime
{
public:
    TimeInvariant()
        : AlarmLineFlagTime(0U, 0U)
    {
    }

    TimeInvariant(const uint8_t hour, const uint8_t minute)
        : AlarmLineFlagTime(hour, minute)
    {
    }

    AlarmLineFlagTime getAlarmLineFlagTime() const
    {
        return AlarmLineFlagTime(m_Hours,m_Minutes);
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

    void consume(const AlarmLineFlagTime &time)
    {
        if (time.m_Hours < HOURS_MAX_VALUE)
        {
            m_Hours = time.m_Hours;
        }
        else
        {
            m_Hours = HOURS_MAX_VALUE;
        }

        if (time.m_Minutes < MINUTES_MAX_VALUE)
        {
            m_Minutes = time.m_Minutes;
        }
        else
        {
            m_Minutes = MINUTES_MAX_VALUE;
        }
    }
};

#endif