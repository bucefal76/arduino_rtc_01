#include "assert.h"
#include "Controller/States/StateBase.hpp"
#include "ViewIf.hpp"

StateBase *StateBase::m_pCurrentState = nullptr;
MenuViewIf *StateBase::m_ExtendedMenuView = nullptr;
TimeSetupViewIf *StateBase::m_pExtendedTimeSetupView = nullptr;
DateSetupViewIf *StateBase::m_pExtendedDateSetupView = nullptr;

RtcDS1302<ThreeWire> *StateBase::m_pRtc = nullptr;
std::map<uint8_t, ViewIf *> StateBase::m_Views;

void StateBase::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateBase::setExtendedViews(MenuViewIf *extendedMenuView,
                                 TimeSetupViewIf *extendedTimeSetupView,
                                 DateSetupViewIf *extendedDateSetupViewIf)
{
    m_ExtendedMenuView = extendedMenuView;
    m_pExtendedTimeSetupView = extendedTimeSetupView;
    m_pExtendedDateSetupView = extendedDateSetupViewIf;
}

void StateBase::addView(ViewIf *pView)
{
    assert(nullptr != pView);
    m_Views[pView->getViewid()] = pView;
}

void StateBase::setRtc(RtcDS1302<ThreeWire> *rtc)
{
    assert(nullptr != rtc);
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

void StateBase::trasitToState(StateBase *pNexState)
{
    m_pCurrentState->exit();

    m_pCurrentState = pNexState;

    m_pCurrentState->enter();
}

ViewIf *StateBase::getView(const uint8_t viewId) const
{
    ViewIf *pView = m_Views[viewId];
    assert(nullptr != pView);
    return pView;
}