#include "States/StateNewTimeConfirmation.hpp"
#include "States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"

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

        trasitToNextState(StateDisplayingTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToNextState(StateDisplayingTime::getInstance());
    }
}

void StateNewTimeConfirmation::enter()
{
    m_pConfirmationView->enable();
}

void StateNewTimeConfirmation::exit()
{
    m_pConfirmationView->disable();
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