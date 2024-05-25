#include "Controller/States/StateAlarmSettings.hpp"
#include "Controller/States/StateAlarmSettingsConfirmation.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "Views/ViewAlarmSettings.hpp"
#include "ModuleConfig.hpp"

StateAlarmSettings StateAlarmSettings::m_Instance;
uint8_t StateAlarmSettings::m_CurrentLineId = 0U;

StateBase *StateAlarmSettings::getInstance()
{
    return &m_Instance;
}

StateAlarmSettings::StateAlarmSettings()
    : m_CurrentCycleId(0U)
{
}

void StateAlarmSettings::setCurrentLineId(const uint8_t currentLineId)
{
    m_CurrentLineId = currentLineId;
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
            if (ALARMS_NO_OF_CYCLES_PER_LINE == (m_CurrentCycleId + 1))
            {
                transitToState(StateAlarmSettingsConfirmation::getInstance());
            }
            else
            {
                m_CurrentCycleId++;
                pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_ON_HOURS);
            }
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            if (0 == m_CurrentCycleId)
            {
                transitToState(StateAlarmSettingsConfirmation::getInstance());
            }
            else
            {
                m_CurrentCycleId--;
                pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_OFF_MINUTES);
            }
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
            m_OnTime[m_CurrentCycleId].decrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_OnTime[m_CurrentCycleId].decrementMinutes();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_OffTime[m_CurrentCycleId].decrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_OffTime[m_CurrentCycleId].decrementMinutes();
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            m_OnTime[m_CurrentCycleId].incrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_OnTime[m_CurrentCycleId].incrementMinutes();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_OffTime[m_CurrentCycleId].incrementHours();
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_OffTime[m_CurrentCycleId].incrementMinutes();
        }
    }

    pViewAlarmSettings->setAlarmCycleToDisplay(m_CurrentCycleId + 1);

    pViewAlarmSettings->setOnTimeToDisplay(m_OnTime[m_CurrentCycleId].getHours(), m_OnTime[m_CurrentCycleId].getMinutes());
    pViewAlarmSettings->setOffTimeToDisplay(m_OffTime[m_CurrentCycleId].getHours(), m_OffTime[m_CurrentCycleId].getMinutes());
}

void StateAlarmSettings::enter()
{
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINE_SETTINGS_VIEW);
    ViewAlarmSettingsIf *pViewAlarmSettings = static_cast<ViewAlarmSettingsIf *>(pExtendedView);

    pViewAlarmSettings->setAlarmIdToDisplay(m_CurrentLineId + 1);
    pViewAlarmSettings->setAlarmCycleToDisplay(m_CurrentCycleId + 1);

    /* TO DO  replace this code with accessing current settings from the EEPROM trough the MODEL*/
    pViewAlarmSettings->setOnTimeToDisplay(m_OnTime[m_CurrentCycleId].getHours(), m_OnTime[m_CurrentCycleId].getMinutes());
    pViewAlarmSettings->setOffTimeToDisplay(m_OffTime[m_CurrentCycleId].getHours(), m_OffTime[m_CurrentCycleId].getMinutes());

    getView(VIEW_ID_LINE_SETTINGS_VIEW)->enable();
}

void StateAlarmSettings::exit()
{
    getView(VIEW_ID_LINE_SETTINGS_VIEW)->disable();
}