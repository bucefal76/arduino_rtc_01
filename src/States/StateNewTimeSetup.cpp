#include "States/StateNewTimeSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "TimeSetupViewIf.hpp"

#include <Arduino.h>

StateNewTimeSetup StateNewTimeSetup::m_Instance;

StateBase *StateNewTimeSetup::getInstance()
{
    return &m_Instance;
}

StateNewTimeSetup::StateNewTimeSetup()
    : m_Hours(12U), m_Minutes(0U)
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
            if (m_Hours >= 24U)
            {
                m_Hours = 0U;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            if (m_Hours > 0U)
            {
                m_Hours--;
            }
            else if (m_Hours == 0U)
            {
                m_Hours = 23U;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            m_pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_MINUTES);
        }

        m_pExtendedTimeSetupView->putHours(m_Hours);
        break;
    }

    case TimeSetupViewIf::TimeSetupViewState::SETUP_MINUTES:
    {
        Serial.println(F("Ustawiam minuty"));

        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Minutes++;
            if (m_Minutes >= 59U)
            {
                m_Minutes = 0U;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            if (m_Minutes > 0U)
            {
                m_Minutes--;
            }
            else if (m_Minutes == 0U)
            {
                m_Minutes = 59U;
            }
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            m_pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_HOURS);
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
    m_pTimeSetupView->enable();

    m_pExtendedTimeSetupView->putHours(m_Hours);
    m_pExtendedTimeSetupView->putMinutes(m_Minutes);
}

void StateNewTimeSetup::exit()
{
    m_pTimeSetupView->disable();
}