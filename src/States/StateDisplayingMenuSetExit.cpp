#include "States/StateDisplayingMenuSetExit.hpp"
#include "States/StateDisplayingMenuSetTime.hpp"
#include "States/StateDisplayingMenuSetDate.hpp"
#include "States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"

static const char *CAPTION_EXIT = "EXIT\0";
static const char *CAPTION_MENU = "MENU\0";

StateDisplayingMenuSetExit StateDisplayingMenuSetExit::m_Instance;

StateBase *StateDisplayingMenuSetExit::getInstance()
{
    return &m_Instance;
}

void StateDisplayingMenuSetExit::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        trasitToNextState(StateDisplayingMenuSetTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToNextState(StateDisplayingMenuSetDate::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NONE != button)
    {
        trasitToNextState(StateDisplayingTime::getInstance());
    }
}

void StateDisplayingMenuSetExit::enter()
{
    m_MenuView->enable();
    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_EXIT);
}

void StateDisplayingMenuSetExit::exit()
{
    m_MenuView->disable();
}
