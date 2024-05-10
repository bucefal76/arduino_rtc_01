#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "Controller/States/StateDisplayingMenuSetDate.hpp"
#include "Controller/States/StateDisplayingMenuSetExit.hpp"
#include "Controller/States/StateNewTimeSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "ModuleConfig.hpp"

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
        trasitToState(StateDisplayingMenuSetDate::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingMenuSetExit::getInstance());
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
        trasitToState(StateNewTimeSetup::getInstance());
    }
}

void StateDisplayingMenuSetTime::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_SET_TIME);
}

void StateDisplayingMenuSetTime::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}
