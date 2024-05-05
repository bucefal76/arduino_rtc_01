#include "States/StateDisplayingMenuSetTime.hpp"
#include "States/StateDisplayingMenuSetDate.hpp"
#include "States/StateDisplayingMenuSetExit.hpp"
#include "States/StateNewTimeSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"

static const char *CAPTION_SET_TIME = "SET TIME\0";
static const char *CAPTION_MENU = "MENU\0";

StateDisplayingMenuSetTime StateDisplayingMenuSetTime::m_Instance;

StateBase *StateDisplayingMenuSetTime::getInstance()
{
    return &m_Instance;
}

void StateDisplayingMenuSetTime::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        trasitToNextState(StateDisplayingMenuSetDate::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToNextState(StateDisplayingMenuSetExit::getInstance());
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
        trasitToNextState(StateNewTimeSetup::getInstance());
    }
}

void StateDisplayingMenuSetTime::enter()
{
    m_MenuView->enable();
    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_SET_TIME);
}

void StateDisplayingMenuSetTime::exit()
{
    m_MenuView->disable();
}
