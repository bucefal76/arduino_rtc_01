#include "Controller/States/StateNewTimeSetup.hpp"
#include "Controller/States/StateNewTimeConfirmation.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "ViewMenuIf.hpp"
#include "ViewTimeSetupIf.hpp"
#include "ModuleConfig.hpp"
#include "SerialPrintAssert.h"

#include <Arduino.h>

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
    ViewTimeSetupIf *pExtendedViewTimeSetup = getMyExtendedView();

    const ViewTimeSetupIf::ViewTimeSetupState currentlyInSetup = pExtendedViewTimeSetup->getState();

    switch (currentlyInSetup)
    {
    case ViewTimeSetupIf::ViewTimeSetupState::SETUP_HOURS:
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
            pExtendedViewTimeSetup->setState(ViewTimeSetupIf::ViewTimeSetupState::SETUP_MINUTES);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            transitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedViewTimeSetup->putHours(m_Hours);
        break;
    }

    case ViewTimeSetupIf::ViewTimeSetupState::SETUP_MINUTES:
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
            pExtendedViewTimeSetup->setState(ViewTimeSetupIf::ViewTimeSetupState::SETUP_HOURS);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            transitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedViewTimeSetup->putMinutes(m_Minutes);
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

    ViewTimeSetupIf *pViewTimeSetup = getMyExtendedView();

    pViewTimeSetup->putHours(m_Hours);
    pViewTimeSetup->putMinutes(m_Minutes);
}

void StateNewTimeSetup::exit()
{
    ViewIf *pView = getView(VIEW_ID_TIME_SETUP_VIEW);
    if (nullptr != pView)
    {
        pView->disable();
    }
}

ViewTimeSetupIf *StateNewTimeSetup::getMyExtendedView() const
{
    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_TIME_SETUP_VIEW);
    RUNTIME_PTR_CHECK(pExtendedView);
    ViewTimeSetupIf *pViewTimeSetup = static_cast<ViewTimeSetupIf *>(pExtendedView);
    RUNTIME_PTR_CHECK(pViewTimeSetup);
    return pViewTimeSetup;
}