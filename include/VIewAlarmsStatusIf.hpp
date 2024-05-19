#ifndef ALARMS_STATUS_VIEW_IF_HPP
#define ALARMS_STATUS_VIEW_IF_HPP

#include <Arduino.h>
#include "ViewExtendedIf.hpp"

class ViewAlarmsStatusIf : public ViewExtendedIf
{
public:
    virtual void setAlarmToDisplay(const uint8_t alarmId) = 0;
};

#endif