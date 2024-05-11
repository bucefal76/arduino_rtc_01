#include "Controller/States/StateNewTimeConfirmation.hpp"
#include "Controller/States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "ModuleConfig.hpp"

StateNewTimeConfirmation StateNewTimeConfirmation::m_Instance;

StateBase *StateNewTimeConfirmation::getInstance()
{
    return &m_Instance;
}

StateNewTimeConfirmation::StateNewTimeConfirmation()
{
}

void StateNewTimeConfirmation::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        setNewTime();

        trasitToState(StateDisplayingTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingTime::getInstance());
    }
}

void StateNewTimeConfirmation::enter()
{
    ViewIf *pView = getView(VIEW_ID_CONFIRMATION_VIEW);
    if (nullptr != pView)
    {
        pView->enable();
    }
}

void StateNewTimeConfirmation::exit()
{
    ViewIf *pView = getView(VIEW_ID_CONFIRMATION_VIEW);
    if (nullptr != pView)
    {
        pView->disable();
    }
}

void StateNewTimeConfirmation::setNewTime()
{
    const RtcDateTime now = m_pRtc->GetDateTime();

    RtcDateTime modifiedTimeDate(now.Year(),
                                 now.Month(),
                                 now.Day(),
                                 m_Hours,
                                 m_Minutes,
                                 0U);

    m_pRtc->SetDateTime(modifiedTimeDate);
}