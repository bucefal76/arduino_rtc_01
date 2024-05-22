#ifndef VIEW_ALARM_STATUS_HPP
#define VIEW_ALARM_STATUS_HPP

#include <Thread.h>

#include "VIewAlarmsStatusIf.hpp"
#include "Views/ViewBase.hpp"

class ViewAlarmSettings : public ViewAlarmsStatusIf, public ViewBase, public Thread
{
public:
    static ViewAlarmSettings *getInstance();

    ViewAlarmSettings();

    /// see ViewIf.
    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();
    /// see ViewAlarmsStatusIf
    virtual void setAlarmToDisplay(const uint8_t alarmId);

private:
    void update();
    static void onRunCallback();

    uint8_t m_AlarmId;

    static ViewAlarmSettings *m_pInstance;
};

#endif