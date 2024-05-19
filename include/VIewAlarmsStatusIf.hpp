#ifndef ALARMS_STATUS_VIEW_IF_HPP
#define ALARMS_STATUS_VIEW_IF_HPP

#include <Arduino.h>
#include "ExtendedViewIf.hpp"

class ViewAlarmsStatusIf : public ExtendedViewIf
{
public:
    virtual void setAlarmToDisplay(const uint8_t alarmId) = 0;
};

#endif