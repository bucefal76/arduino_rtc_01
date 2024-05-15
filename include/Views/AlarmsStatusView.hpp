#ifndef ALARMS_STATUS_VIEW_HPP
#define ALARMS_STATUS_VIEW_HPP

#include "Views/BaseView.hpp"
#include <Thread.h>

class AlarmsStatusView : public BaseView, public Thread
{
public:
    static AlarmsStatusView *getInstance();

    AlarmsStatusView();

    /// see ViewIf.
    virtual uint8_t getViewid() const;
    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    uint8_t m_AlarmId;

    static AlarmsStatusView *m_pInstance;
};

#endif