#ifndef STATE_ALARM_SETTINGS_CONFIRMATION_HPP
#define STATE_ALARM_SETTINGS_CONFIRMATION_HPP

/*
    This state controls the device's behavior when it asks the operator to accept
    the newly entered alarm settings for selected output line. A confirmation dialog - are you sure?
*/

#include "Controller/States/StateAlarmSettings.hpp"

class StateAlarmSettingsConfirmation : public StateAlarmSettings
{
public:
    static StateBase *getInstance();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

private:
    StateAlarmSettingsConfirmation();

    virtual void enter();
    virtual void exit();

    bool applySettings();

    static StateAlarmSettingsConfirmation m_Instance;
};

#endif