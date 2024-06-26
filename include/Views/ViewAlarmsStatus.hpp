#ifndef ALARMS_STATUS_VIEW_HPP
#define ALARMS_STATUS_VIEW_HPP

#include <Thread.h>

#include "Views/ViewBase.hpp"
#include "ViewAlarmsStatusIf.hpp"

/*
    This view shows statuses of the alarm lines.
*/

class ViewAlarmsStatus : public ViewBase, public Thread, public ViewAlarmsStatusIf
{
public:
    static ViewAlarmsStatus *getInstance();

    ViewAlarmsStatus();

    /// see ViewIf.
    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();
    /// see ViewAlarmsStatusIf
    virtual void setAlarmIdToDisplay(const uint8_t alarmId);

private:
    void update();
    static void onRunCallback();

    uint8_t m_AlarmLineId;

    static ViewAlarmsStatus *m_pInstance;
};

#endif