#include "Controller/States/StateDisplayAlarmsStatus.hpp"
#include "ModuleConfig.hpp"
#include "ViewIf.hpp"
#include "AlarmsStatusViewIf.hpp"

#define ALARM_ID_MAX_VALUE ALARMS_NO_OF_ALARMS
#define ALARM_ID_MIN_VALUE 1U

StateDisplayAlarmsStatus StateDisplayAlarmsStatus::m_Instance;

StateBase *StateDisplayAlarmsStatus::getInstance()
{
    return &m_Instance;
}

StateDisplayAlarmsStatus::StateDisplayAlarmsStatus()
    : m_AlarmId(ALARM_ID_MIN_VALUE)
{
}

void StateDisplayAlarmsStatus::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
    {
        m_AlarmId--;
        if (m_AlarmId < ALARM_ID_MIN_VALUE)
        {
            m_AlarmId = ALARM_ID_MAX_VALUE;
        }

        AlarmsStatusViewIf *pAlarmStatusView = getAlarmsStatusView();
        pAlarmStatusView->setAlarmToDisplay(m_AlarmId);
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
        m_AlarmId++;
        if (m_AlarmId > ALARM_ID_MAX_VALUE)
        {
            m_AlarmId = ALARM_ID_MIN_VALUE;
        }

        AlarmsStatusViewIf *pAlarmStatusView = getAlarmsStatusView();
        pAlarmStatusView->setAlarmToDisplay(m_AlarmId);
    }
}

void StateDisplayAlarmsStatus::enter()
{
    getView(VIEW_ID_ALARMS_STATUS_VIEW)->enable();
}

void StateDisplayAlarmsStatus::exit()
{
    getView(VIEW_ID_ALARMS_STATUS_VIEW)->disable();
}

AlarmsStatusViewIf *StateDisplayAlarmsStatus::getAlarmsStatusView()
{
    ExtendedViewIf *pExtendedView = getExtendedView(VIEW_ID_ALARMS_STATUS_VIEW);
    AlarmsStatusViewIf *pAlarmStatusView = static_cast<AlarmsStatusViewIf *>(pExtendedView);
    return pAlarmStatusView;
}