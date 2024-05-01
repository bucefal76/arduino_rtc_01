#include <avr/pgmspace.h>

#include "States/StateDisplayingMenuSetDate.hpp"
#include "States/StateDisplayingMenuSetTime.hpp"
#include "States/StateDisplayingMenuSetExit.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"

static const char *CAPTION_SET_DATE = "SET DATE\0";

StateDisplayingMenuSetDate StateDisplayingMenuSetDate::m_Instance;

StateBase *StateDisplayingMenuSetDate::getInstance()
{
    return &m_Instance;
}

void StateDisplayingMenuSetDate::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        trasitToNextState(StateDisplayingMenuSetExit::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToNextState(StateDisplayingMenuSetTime::getInstance());
    }
}

void StateDisplayingMenuSetDate::enter()
{
    m_MenuView->enable();
    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_SET_DATE);
}

void StateDisplayingMenuSetDate::exit()
{
    m_MenuView->disable();
}