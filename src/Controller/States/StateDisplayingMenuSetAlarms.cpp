#include "Controller/States/StateDisplayingMenuSetAlarms.hpp"
#include "Controller/States/StateDisplayingMenuSetDate.hpp"
#include "Controller/States/StateDisplayingMenuSetExit.hpp"
#include "Controller/States/StateDisplayAlarmsStatus.hpp"
#include "Controller/States/StateNewTimeSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "ModuleConfig.hpp"

static const char *CAPTION_SET_ALARMS = "SET ALARMS\0";
static const char *CAPTION_MENU = "MENU\0";

StateDisplayingMenuSetAlarms StateDisplayingMenuSetAlarms::m_Instance;

StateBase *StateDisplayingMenuSetAlarms::getInstance()
{
    return &m_Instance;
}

StateDisplayingMenuSetAlarms::StateDisplayingMenuSetAlarms()
{
}

void StateDisplayingMenuSetAlarms::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        trasitToState(StateDisplayingMenuSetExit::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingMenuSetDate::getInstance());
    }
    else if ((KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button) || (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button))
    {
        trasitToState(StateDisplayAlarmsStatus::getInstance());
    }
}

void StateDisplayingMenuSetAlarms::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    m_ExtendedMenuView->setTitle(CAPTION_MENU);
    m_ExtendedMenuView->setContent(CAPTION_SET_ALARMS);
}

void StateDisplayingMenuSetAlarms::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}