#include "States/StateNewDateConfirmation.hpp"
#include "States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"

StateNewDateConfirmation StateNewDateConfirmation::m_Instance;

StateBase *StateNewDateConfirmation::getInstance()
{
    return &m_Instance;
}

StateNewDateConfirmation::StateNewDateConfirmation()
{
}

void StateNewDateConfirmation::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        setNewDate();

        trasitToState(StateDisplayingTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingTime::getInstance());
    }
}

void StateNewDateConfirmation::setNewDate()
{
    const RtcDateTime now = m_pRtc->GetDateTime();

    RtcDateTime modifiedTimeDate(m_Year,
                                 m_Month,
                                 m_Day,
                                 now.Hour(),
                                 now.Minute(),
                                 now.Second());

    m_pRtc->SetDateTime(modifiedTimeDate);
}

void StateNewDateConfirmation::enter()
{
    m_pConfirmationView->enable();
}

void StateNewDateConfirmation::exit()
{
    m_pConfirmationView->disable();
}