#include "Controller/States/StateDisplayAlarmsStatus.hpp"
#include "Controller/States/StateDisplayingMenuSetAlarms.hpp"
#include "Controller/States/StateAlarmSettings.hpp"
#include "ModuleConfig.hpp"
#include "ViewIf.hpp"
#include "ViewAlarmsStatusIf.hpp"

#define ALARM_ID_MAX_VALUE ALARMS_NO_OF_LINES
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
        transitToState(StateAlarmSettings::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        transitToState(StateDisplayingMenuSetAlarms::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
    {
        m_AlarmId--;
        if (m_AlarmId < ALARM_ID_MIN_VALUE)
        {
            m_AlarmId = ALARM_ID_MAX_VALUE;
        }

        ViewAlarmsStatusIf *pAlarmStatusView = getViewAlarmsStatus();
        pAlarmStatusView->setAlarmIdToDisplay(m_AlarmId);
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
        m_AlarmId++;
        if (m_AlarmId > ALARM_ID_MAX_VALUE)
        {
            m_AlarmId = ALARM_ID_MIN_VALUE;
        }

        ViewAlarmsStatusIf *pAlarmStatusView = getViewAlarmsStatus();
        pAlarmStatusView->setAlarmIdToDisplay(m_AlarmId);
    }
}

void StateDisplayAlarmsStatus::enter()
{
    getView(VIEW_ID_LINES_STATUS_VIEW)->enable();
}

void StateDisplayAlarmsStatus::exit()
{
    getView(VIEW_ID_LINES_STATUS_VIEW)->disable();
}

ViewAlarmsStatusIf *StateDisplayAlarmsStatus::getViewAlarmsStatus()
{
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINES_STATUS_VIEW);
    ViewAlarmsStatusIf *pAlarmStatusView = static_cast<ViewAlarmsStatusIf *>(pExtendedView);
    return pAlarmStatusView;
}