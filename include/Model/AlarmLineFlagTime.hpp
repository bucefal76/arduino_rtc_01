#ifndef ALARM_LINE_FLAG_TIME_HPP
#define ALARM_LINE_FLAG_TIME_HPP

struct AlarmLineFlagTime
{
    uint8_t m_Hours;
    uint8_t m_Minutes;

    AlarmLineFlagTime()
        : m_Hours(0U),
          m_Minutes(0U)
    {
    }
};

#endif