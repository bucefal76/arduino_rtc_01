#include "States/StateBase.hpp"
#include "ViewIf.hpp"

StateBase *StateBase::m_pCurrentState = nullptr;
ViewIf *StateBase::m_TimeView = nullptr;
ViewIf *StateBase::m_MenuView = nullptr;
MenuViewIf *StateBase::m_ExtendedMenuView = nullptr;
ViewIf *StateBase::m_pTimeSetupView = nullptr;
TimeSetupViewIf *StateBase::m_pExtendedTimeSetupView = nullptr;
ViewIf *StateBase::m_pConfirmationView = nullptr;
RtcDS1302<ThreeWire> *StateBase::m_pRtc = nullptr;

void StateBase::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateBase::setViews(ViewIf *timeView,
                         ViewIf *menuView,
                         MenuViewIf *extendedMenuView,
                         ViewIf *timeSetupView,
                         TimeSetupViewIf *extendedTimeSetupView,
                         ViewIf *confirmationView)
{
    m_TimeView = timeView;
    m_MenuView = menuView;
    m_ExtendedMenuView = extendedMenuView;
    m_pTimeSetupView = timeSetupView;
    m_pExtendedTimeSetupView = extendedTimeSetupView;
    m_pConfirmationView = confirmationView;
}

void StateBase::setRtc(RtcDS1302<ThreeWire> *rtc)
{
    m_pRtc = rtc;
}

StateBase *StateBase::getCurrentState()
{
    return m_pCurrentState;
}

void StateBase::setCurrentState(StateBase *state)
{
    m_pCurrentState = state;
}

void StateBase::trasitToNextState(StateBase *pNexState)
{
    m_pCurrentState->exit();

    m_pCurrentState = pNexState;

    m_pCurrentState->enter();
}