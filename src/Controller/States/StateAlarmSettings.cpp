#include "Controller/States/StateAlarmSettings.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "Views/ViewAlarmSettings.hpp"
#include "ModuleConfig.hpp"

StateAlarmSettings StateAlarmSettings::m_Instance;

StateBase *StateAlarmSettings::getInstance()
{
    return &m_Instance;
}

StateAlarmSettings::StateAlarmSettings()
{
}

void StateAlarmSettings::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
    }
}

void StateAlarmSettings::enter()
{
    
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINE_SETTINGS_VIEW);
    ViewAlarmSettingsIf *pViewAlarmSettings = static_cast<ViewAlarmSettingsIf *>(pExtendedView);

    pViewAlarmSettings->setOnTimeToDisplay(11, 55);
    pViewAlarmSettings->setOffTimeToDisplay(12, 5);
    

    getView(VIEW_ID_LINE_SETTINGS_VIEW)->enable();
}

void StateAlarmSettings::exit()
{
    getView(VIEW_ID_LINE_SETTINGS_VIEW)->disable();
}