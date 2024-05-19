#include <avr/pgmspace.h>

#include "Controller/States/StateDisplayingMenuSetDate.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "Controller/States/StateDisplayingMenuSetAlarms.hpp"
#include "Controller/States/StateNewDateSetup.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "ViewMenuIf.hpp"
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
        transitToState(StateDisplayingMenuSetAlarms::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        transitToState(StateDisplayingMenuSetTime::getInstance());
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
        transitToState(StateNewDateSetup::getInstance());
    }
}

void StateDisplayingMenuSetDate::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_MENU_VIEW);
    ViewMenuIf *pViewMenu = static_cast<ViewMenuIf *>(pExtendedView);

    pViewMenu->setTitle(CAPTION_MENU);
    pViewMenu->setContent(CAPTION_SET_DATE);
}

void StateDisplayingMenuSetDate::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}