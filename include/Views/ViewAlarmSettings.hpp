#ifndef VIEW_ALARM_STATUS_HPP
#define VIEW_ALARM_STATUS_HPP

#include <Thread.h>

#include "ViewAlarmsSettingsIf.hpp"
#include "Views/ViewBase.hpp"

class ViewAlarmSettings : public ViewAlarmSettingsIf, public ViewBase, public Thread
{
public:
    static ViewAlarmSettings *getInstance();

    ViewAlarmSettings();

    /// see ViewIf.
    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();
    //  see ViewTimeSettingsIf
    virtual void setState(const ViewAlarmSettingsState newState);
    virtual ViewAlarmSettingsIf::ViewAlarmSettingsState getState() const;
    virtual void setAlarmIdToDisplay(const uint8_t alarmId);
    virtual void setAlarmCycleToDisplay(const uint8_t alarmCycleId);
    virtual void setOnTimeToDisplay(const uint8_t hours, const uint8_t minutes);
    virtual void setOffTimeToDisplay(const uint8_t hours, const uint8_t minutes);

private:
    void update();
    static void onRunCallback();
    bool isAlarmCycleActive() const;

    uint8_t m_AlarmLineId;
    uint8_t m_CycleId;
    uint8_t m_pOnTimeHours;
    uint8_t m_pOnTimeMinutes;
    uint8_t m_pOffTimeHours;
    uint8_t m_pOffTimeMinutes;

    ViewAlarmSettingsIf::ViewAlarmSettingsState m_State;

    static ViewAlarmSettings *m_pInstance;
};

#endif