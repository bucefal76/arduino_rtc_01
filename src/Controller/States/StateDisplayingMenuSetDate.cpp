#include <avr/pgmspace.h>

#include "Controller/States/StateDisplayingMenuSetDate.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "Controller/States/StateDisplayingMenuSetExit.hpp"
#include "Controller/States/StateNewDateSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "ModuleConfig.hpp"

static const char *CAPTION_SET_DATE = "SET DATE\0";
static const char *CAPTION_MENU = "MENU\0";

StateDisplayingMenuSetDate StateDisplayingMenuSetDate::m_Instance;

StateBase *StateDisplayingMenuSetDate::getInstance()
{
    return &m_Instance;
}

StateDisplayingMenuSetDate::StateDisplayingMenuSetDate()
{
}

void StateDisplayingMenuSetDate::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        trasitToState(StateDisplayingMenuSetExit::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingMenuSetTime::getInstance());
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
        trasitToState(StateNewDateSetup::getInstance());
    }
}

void StateDisplayingMenuSetDate::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_SET_DATE);
}

void StateDisplayingMenuSetDate::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}