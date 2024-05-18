#include "Controller/States/StateDisplayAlarmsStatus.hpp"
#include "ModuleConfig.hpp"
#include "ViewIf.hpp"

StateDisplayAlarmsStatus StateDisplayAlarmsStatus::m_Instance;

StateBase *StateDisplayAlarmsStatus::getInstance()
{
    return &m_Instance;
}

StateDisplayAlarmsStatus::StateDisplayAlarmsStatus()
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
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
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