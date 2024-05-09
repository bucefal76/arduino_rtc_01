#include "States/StateDisplayingMenuSetExit.hpp"
#include "States/StateDisplayingMenuSetTime.hpp"
#include "States/StateDisplayingMenuSetDate.hpp"
#include "States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "ModuleConfig.hpp"

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
        trasitToState(StateDisplayingMenuSetTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingMenuSetDate::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NONE != button)
    {
        trasitToState(StateDisplayingTime::getInstance());
    }
}

void StateDisplayingMenuSetExit::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_EXIT);
}

void StateDisplayingMenuSetExit::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}
