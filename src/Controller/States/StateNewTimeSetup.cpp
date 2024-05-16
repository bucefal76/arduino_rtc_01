#include "Controller/States/StateNewTimeSetup.hpp"
#include "Controller/States/StateNewTimeConfirmation.hpp"
#include "ViewIf.hpp"
#include "ExtendedViewIf.hpp"
#include "MenuViewIf.hpp"
#include "TimeSetupViewIf.hpp"
#include "ModuleConfig.hpp"
#include "SerialPrintAssert.h"

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
    TimeSetupViewIf *pExtendedTimeSetupView = getMyExtendedView();

    const TimeSetupViewIf::TimeSetupViewState currentlyInSetup = pExtendedTimeSetupView->getState();

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
            pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_MINUTES);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            trasitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedTimeSetupView->putHours(m_Hours);
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
            pExtendedTimeSetupView->setState(TimeSetupViewIf::TimeSetupViewState::SETUP_HOURS);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            trasitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedTimeSetupView->putMinutes(m_Minutes);
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

    TimeSetupViewIf *pTimeSetupView = getMyExtendedView();

    pTimeSetupView->putHours(m_Hours);
    pTimeSetupView->putMinutes(m_Minutes);
}

void StateNewTimeSetup::exit()
{
    ViewIf *pView = getView(VIEW_ID_TIME_SETUP_VIEW);
    if (nullptr != pView)
    {
        pView->disable();
    }
}

TimeSetupViewIf *StateNewTimeSetup::getMyExtendedView() const
{
    ExtendedViewIf *pExtendedView = getExtendedView(VIEW_ID_TIME_SETUP_VIEW);
    RUNTIME_PTR_CHECK(pExtendedView);
    TimeSetupViewIf *pTimeSetupView = static_cast<TimeSetupViewIf *>(pExtendedView);
    RUNTIME_PTR_CHECK(pTimeSetupView);
    return pTimeSetupView;
}