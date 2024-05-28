#include "Controller/States/StateAlarmSettings.hpp"
#include "Controller/States/StateAlarmSettingsConfirmation.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "Views/ViewAlarmSettings.hpp"
#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"

StateAlarmSettings StateAlarmSettings::m_Instance;
uint8_t StateAlarmSettings::m_AlarmLineId = 0U;

StateBase *StateAlarmSettings::getInstance()
{
    return &m_Instance;
}

StateAlarmSettings::StateAlarmSettings()
    : m_CycleId(0U)
{
}

void StateAlarmSettings::setCurrentLineId(const uint8_t currentLineId)
{
    m_AlarmLineId = currentLineId;
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
            if (ALARMS_NO_OF_CYCLES_PER_LINE == (m_CycleId + 1))
            {
                transitToState(StateAlarmSettingsConfirmation::getInstance());
            }
            else
            {
                m_CycleId++;
                pViewAlarmSettings->setState(ViewAlarmSettingsIf::SETUP_ON_HOURS);
            }
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            if (0 == m_CycleId)
            {
                transitToState(StateAlarmSettingsConfirmation::getInstance());
            }
            else
            {
                m_CycleId--;
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
            m_pModel->incrementOnHours(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_pModel->decrementOnMinutes(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_pModel->decrementOffHours(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_pModel->decrementOffMinutes(m_AlarmLineId, m_CycleId);
        }
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
    {
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == viewState)
        {
            m_pModel->incrementOnHours(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == viewState)
        {
            m_pModel->incrementOnMinutes(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == viewState)
        {
            m_pModel->incrementOffHours(m_AlarmLineId, m_CycleId);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_MINUTES == viewState)
        {
            m_pModel->incrementOffMinutes(m_AlarmLineId, m_CycleId);
        }
    }

    pViewAlarmSettings->setAlarmCycleToDisplay(m_CycleId + 1);

    pViewAlarmSettings->setOnTimeToDisplay(m_pModelState->getAlarmLineOnTime(m_AlarmLineId, m_CycleId).m_Hours,
                                           m_pModelState->getAlarmLineOnTime(m_AlarmLineId, m_CycleId).m_Minutes);
    pViewAlarmSettings->setOffTimeToDisplay(m_pModelState->getAlarmLineOffTime(m_AlarmLineId, m_CycleId).m_Hours,
                                            m_pModelState->getAlarmLineOffTime(m_AlarmLineId, m_CycleId).m_Minutes);
}

void StateAlarmSettings::enter()
{
    m_AlarmLineId = 0;

    // TODO read model back from eeprom!

    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_LINE_SETTINGS_VIEW);
    ViewAlarmSettingsIf *pViewAlarmSettings = static_cast<ViewAlarmSettingsIf *>(pExtendedView);

    pViewAlarmSettings->setAlarmIdToDisplay(m_AlarmLineId + 1);
    pViewAlarmSettings->setAlarmCycleToDisplay(m_CycleId + 1);

    pViewAlarmSettings->setOnTimeToDisplay(m_pModelState->getAlarmLineOnTime(m_AlarmLineId, m_CycleId).m_Hours,
                                           m_pModelState->getAlarmLineOnTime(m_AlarmLineId, m_CycleId).m_Minutes);
    pViewAlarmSettings->setOffTimeToDisplay(m_pModelState->getAlarmLineOffTime(m_AlarmLineId, m_CycleId).m_Hours,
                                            m_pModelState->getAlarmLineOffTime(m_AlarmLineId, m_CycleId).m_Minutes);

    getView(VIEW_ID_LINE_SETTINGS_VIEW)->enable();
}

void StateAlarmSettings::exit()
{
    getView(VIEW_ID_LINE_SETTINGS_VIEW)->disable();
}