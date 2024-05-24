#ifndef VIEW_ALARM_SETTINGS_IF_HPP
#define VIEW_ALARM_SETTINGS_IF_HPP

#include "ViewExtendedIf.hpp"

class ViewAlarmSettingsIf : public ViewExtendedIf
{
public:
    enum ViewAlarmSettingsState
    {
        SETUP_ON_HOURS,
        SETUP_ON_MINUTES,
        SETUP_OFF_HOURS,
        SETUP_OFF_MINUTES
    };

    virtual void setState(const ViewAlarmSettingsState newState) = 0;
    virtual ViewAlarmSettingsState getState() const = 0;
    virtual void setAlarmToDisplay(const uint8_t alarmId) = 0;
    virtual void setOnTimeToDisplay(const uint8_t hours, const uint8_t minutes) = 0;
    virtual void setOffTimeToDisplay(const uint8_t hours, const uint8_t minutes) = 0;
};

#endif