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
    : m_OnTime(11, 55), m_OffTime(14, 30)
{
}

void StateAlarmSettings::processButton(const KeyboardControllerIf::ButtonCode button)
{
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINE_SETTINGS_VIEW);
    ViewAlarmSettingsIf *pViewAlarmSettings = static_cast<ViewAlarmSettingsIf *>(pExtendedView);

    const ViewAlarmSettingsIf::ViewAlarmSettingsState viewState = pViewAlarmSettings->getState();

    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_ON_MINUTES);
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_OFF_HOURS);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_OFF_MINUTES);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            // TODO
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            // TODO
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_ON_HOURS);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_ON_MINUTES);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_OFF_HOURS);
        }
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button))
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            m_OnTime.decrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_OnTime.decrementMinutes();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_OffTime.decrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_OffTime.decrementMinutes();
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            m_OnTime.incrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_OnTime.incrementMinutes();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_OffTime.incrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_OffTime.incrementMinutes();
        }
    }

    pViewAlarmSettings->setOnTimeToDisplay(m_OnTime.getHours(), m_OnTime.getMinutes());
    pViewAlarmSettings->setOffTimeToDisplay(m_OffTime.getHours(), m_OffTime.getMinutes());
}

void StateAlarmSettings::enter()
{

    /* TO DO  replace this code with accessing current settings from the EEPROM trough the MODEL*/
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINE_SETTINGS_VIEW);
    ViewAlarmSettingsIf *pViewAlarmSettings = static_cast<ViewAlarmSettingsIf *>(pExtendedView);

    pViewAlarmSettings->setOnTimeToDisplay(m_OnTime.getHours(), m_OnTime.getMinutes());
    pViewAlarmSettings->setOffTimeToDisplay(m_OffTime.getHours(), m_OffTime.getMinutes());

    getView(VIEW_ID_LINE_SETTINGS_VIEW)->enable();
}

void StateAlarmSettings::exit()
{
    getView(VIEW_ID_LINE_SETTINGS_VIEW)->disable();
}