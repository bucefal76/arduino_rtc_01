#ifndef ALARM_LINE_FLAG_TIME_HPP
#define ALARM_LINE_FLAG_TIME_HPP

struct AlarmLineFlagTime
{
    AlarmLineFlagTime()
        : m_Hours(0U),
          m_Minutes(0U)
    {
    }

    AlarmLineFlagTime(const uint8_t hour, const uint8_t minute)
        : m_Hours(hour), m_Minutes(minute)
    {
    }

    uint8_t m_Hours;
    uint8_t m_Minutes;
};

#endif