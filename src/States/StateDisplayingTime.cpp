#include "States/StateDisplayingTime.hpp"
#include "States/StateDisplayingMenuSetTime.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"

StateDisplayingTime StateDisplayingTime::m_Instance;

StateBase *StateDisplayingTime::getInstance()
{
    return &m_Instance;
}

void StateDisplayingTime::processButton(const KeyboardControllerIf::ButtonCode button)
{
    trasitToNextState(StateDisplayingMenuSetTime::getInstance());
}

void StateDisplayingTime::exit()
{
    m_TimeView->disable();
}