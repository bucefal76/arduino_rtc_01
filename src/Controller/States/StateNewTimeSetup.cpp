#include "Controller/States/StateNewTimeSetup.hpp"
#include "Controller/States/StateNewTimeConfirmation.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "TimeSetupViewIf.hpp"
#include "ModuleConfig.hpp"

#include <Arduino.h>

#define HOURS_MAX_VALUE 23U
#define HOURS_MIN_VALUE 0U
#define MINUTES_MAX_VALUE 59U
#define MINUTES_MIN_VALUE 0U

uint8_t StateNewTimeSetup::m_Hours = 12U;
uint8_t StateNewTimeSetup::m_Minutes = 0U;

StateNewTimeSetup StateNewTimeSetup::m_Instance;

StateBase *StateNewTimeSetup::getInstance()
{
    return &m_Instance;
}

StateNewTimeSetup::StateNewTimeSetup()
{
}

void StateNewTimeSetup::processButton(const KeyboardControllerIf::ButtonCode button)
{
    const TimeSetupViewIf::TimeSetupViewState currentlyInSetup = m_pExtendedTimeSetupView->getState();

    switch (currentlyInSetup)
    {
    case TimeSetupViewIf::TimeSetupViewState::SETUP_HOURS:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Hours++;
            if (m_Hours > HOURS_MAX_VALUE)
            {
                m_Hours = HOURS_MIN_VALUE;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            if (m_Hours > HOURS_MIN_VALUE)
            {
                m_Hours--;
            }
            else if (m_Hours == HOURS_MIN_VALUE)
            {
                m_Hours = HOURS_MAX_VALUE;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            m_pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_MINUTES);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            trasitToState(StateNewTimeConfirmation::getInstance());
        }

        m_pExtendedTimeSetupView->putHours(m_Hours);
        break;
    }

    case TimeSetupViewIf::TimeSetupViewState::SETUP_MINUTES:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Minutes++;
            if (m_Minutes > MINUTES_MAX_VALUE)
            {
                m_Minutes = MINUTES_MIN_VALUE;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            if (m_Minutes > MINUTES_MIN_VALUE)
            {
                m_Minutes--;
            }
            else if (m_Minutes == MINUTES_MIN_VALUE)
            {
                m_Minutes = MINUTES_MAX_VALUE;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            m_pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_HOURS);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            trasitToState(StateNewTimeConfirmation::getInstance());
        }

        m_pExtendedTimeSetupView->putMinutes(m_Minutes);
        break;
    }

    default:

        break;
    }
}

void StateNewTimeSetup::enter()
{
    ViewIf *pView = getView(VIEW_ID_TIME_SETUP_VIEW);
    if (nullptr != pView)
    {
        pView->enable();
    }

    m_pExtendedTimeSetupView->putHours(m_Hours);
    m_pExtendedTimeSetupView->putMinutes(m_Minutes);
}

void StateNewTimeSetup::exit()
{
    ViewIf *pView = getView(VIEW_ID_TIME_SETUP_VIEW);
    if (nullptr != pView)
    {
        pView->disable();
    }
}
