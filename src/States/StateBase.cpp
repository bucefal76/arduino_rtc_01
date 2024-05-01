#include "States/StateBase.hpp"
#include "ViewIf.hpp"

StateBase *StateBase::m_pCurrentState = nullptr;
ViewIf *StateBase::m_TimeView = nullptr;
ViewIf *StateBase::m_MenuView = nullptr;
MenuViewIf *StateBase::m_ExtendedMenuView = nullptr;

void StateBase::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateBase::setViews(ViewIf *timeView, ViewIf *menuView, MenuViewIf *extendedMenuView)
{
    m_TimeView = timeView;
    m_MenuView = menuView;
    m_ExtendedMenuView = extendedMenuView;
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