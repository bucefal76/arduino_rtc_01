#ifndef ALARMS_STATUS_VIEW_HPP
#define ALARMS_STATUS_VIEW_HPP

#include <Thread.h>

#include "Views/BaseView.hpp"
#include "AlarmsStatusViewIf.hpp"

class AlarmsStatusView : public BaseView, public Thread, public AlarmsStatusViewIf
{
public:
    static AlarmsStatusView *getInstance();

    AlarmsStatusView();

    /// see ViewIf.
    virtual uint8_t getViewid() const;
    virtual void enable();
    virtual void disable();
    /// see AlarmsStatusViewIf
    virtual void setAlarmToDisplay(const uint8_t alarmId);

private:
    void update();
    static void onRunCallback();

    uint8_t m_AlarmId;

    static AlarmsStatusView *m_pInstance;
};

#endif