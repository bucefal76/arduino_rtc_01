#include "Controller/States/StateDisplayingTime.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "ViewIf.hpp"
#include "ViewMenuIf.hpp"
#include "ModuleConfig.hpp"

#include <Arduino.h>

StateDisplayingTime StateDisplayingTime::m_Instance;

StateBase *StateDisplayingTime::getInstance()
{
    return &m_Instance;
}

StateDisplayingTime::StateDisplayingTime()
{
}

void StateDisplayingTime::processButton(const KeyboardControllerIf::ButtonCode button)
{
    transitToState(StateDisplayingMenuSetTime::getInstance());
}

void StateDisplayingTime::enter()
{
    getView(VIEW_ID_TIME_VIEW)->enable();
}

void StateDisplayingTime::exit()
{
    getView(VIEW_ID_TIME_VIEW)->disable();
}