#include "Controller/States/StateDisplayingMenuSetExit.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "Controller/States/StateDisplayingMenuSetAlarms.hpp"
#include "Controller/States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "ViewMenuIf.hpp"
#include "ModuleConfig.hpp"

static const char *CAPTION_EXIT = "EXIT\0";
static const char *CAPTION_MENU = "MENU\0";

StateDisplayingMenuSetExit StateDisplayingMenuSetExit::m_Instance;

StateBase *StateDisplayingMenuSetExit::getInstance()
{
    return &m_Instance;
}

StateDisplayingMenuSetExit::StateDisplayingMenuSetExit()
{
}

void StateDisplayingMenuSetExit::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        transitToState(StateDisplayingMenuSetTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        transitToState(StateDisplayingMenuSetAlarms::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NONE != button)
    {
        transitToState(StateDisplayingTime::getInstance());
    }
}

void StateDisplayingMenuSetExit::enter()
{
    getView(VIEW_ID_MENU_VIEW)->enable();

    ViewExtendedIf *pExtendedView = getExtendedView(VIEW_ID_MENU_VIEW);
    ViewMenuIf *pViewMenu = static_cast<ViewMenuIf *>(pExtendedView);

    pViewMenu->setTitle(CAPTION_MENU);
    pViewMenu->setContent(CAPTION_EXIT);
}

void StateDisplayingMenuSetExit::exit()
{
    getView(VIEW_ID_MENU_VIEW)->disable();
}
