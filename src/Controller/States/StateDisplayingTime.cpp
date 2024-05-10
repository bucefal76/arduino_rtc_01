#include "Controller/States/StateDisplayingTime.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"
#include "ModuleConfig.hpp"

#include <Arduino.h>

StateDisplayingTime StateDisplayingTime::m_Instance;

StateBase *StateDisplayingTime::getInstance()
{
    return &m_Instance;
}

void StateDisplayingTime::processButton(const KeyboardControllerIf::ButtonCode button)
{
    trasitToState(StateDisplayingMenuSetTime::getInstance());
}

void StateDisplayingTime::enter()
{
    getView(VIEW_ID_TIME_VIEW)->enable();
}

void StateDisplayingTime::exit()
{
    getView(VIEW_ID_TIME_VIEW)->disable();
}