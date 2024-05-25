#include "Controller/States/StateNewTimeSetup.hpp"
#include "Controller/States/StateNewTimeConfirmation.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "ViewMenuIf.hpp"
#include "ViewTimeSetupIf.hpp"
#include "ModuleConfig.hpp"
#include "SerialPrintAssert.h"

#include <Arduino.h>

TimeInvariant StateNewTimeSetup::m_Time(11, 55);

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
            m_Time.incrementHours();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            m_Time.decrementHours();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            pExtendedViewTimeSetup->setState(ViewTimeSetupIf::ViewTimeSetupState::SETUP_MINUTES);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            transitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedViewTimeSetup->putHours(m_Time.getHours());
        break;
    }

    case ViewTimeSetupIf::ViewTimeSetupState::SETUP_MINUTES:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Time.incrementMinutes();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            m_Time.decrementMinutes();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            pExtendedViewTimeSetup->setState(ViewTimeSetupIf::ViewTimeSetupState::SETUP_HOURS);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            transitToState(StateNewTimeConfirmation::getInstance());
        }

        pExtendedViewTimeSetup->putMinutes(m_Time.getMinutes());
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

    pViewTimeSetup->putHours(m_Time.getHours());
    pViewTimeSetup->putMinutes(m_Time.getMinutes());
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