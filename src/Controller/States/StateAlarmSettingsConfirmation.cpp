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
    return m_pModel->saveAlarmLinesSettingsToEEPROM();
}