#include "Controller/States/StateAlarmSettingsConfirmation.hpp"
#include "Controller/States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"

StateAlarmSettingsConfirmation StateAlarmSettingsConfirmation::m_Instance;

StateBase *StateAlarmSettingsConfirmation::getInstance()
{
    return &m_Instance;
}

StateAlarmSettingsConfirmation::StateAlarmSettingsConfirmation()
{
}

void StateAlarmSettingsConfirmation::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        if (applySettings())
        {
            transitToState(StateDisplayingTime::getInstance());
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        transitToState(StateDisplayingTime::getInstance());
    }
}

void StateAlarmSettingsConfirmation::enter()
{
    getView(VIEW_ID_CONFIRMATION_VIEW)->enable();
}

void StateAlarmSettingsConfirmation::exit()
{
    getView(VIEW_ID_CONFIRMATION_VIEW)->disable();
}

bool StateAlarmSettingsConfirmation::applySettings()
{
    for (uint8_t alarmCycleIt = 0; alarmCycleIt < ALARMS_NO_OF_CYCLES_PER_LINE; alarmCycleIt++)
    {
        if (false == m_pModel->setAlarmLineOnTime(m_AlarmLineId, alarmCycleIt, m_OnTime[alarmCycleIt]))
        {
            return false;
        }
        if (false == m_pModel->setAlarmLineOffTime(m_AlarmLineId, alarmCycleIt, m_OffTime[alarmCycleIt]))
        {
            return false;
        }
    }

    return true;
}