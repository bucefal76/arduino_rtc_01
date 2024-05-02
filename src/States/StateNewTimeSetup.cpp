#include "States/StateNewTimeSetup.hpp"
#include "ViewIf.hpp"
#include "MenuViewIf.hpp"

#include <Arduino.h>

StateNewTimeSetup StateNewTimeSetup::m_Instance;

StateBase *StateNewTimeSetup::getInstance()
{
    return &m_Instance;
}

void StateNewTimeSetup::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateNewTimeSetup::enter()
{
    m_pTimeSetupView->enable();
}

void StateNewTimeSetup::exit()
{
    m_pTimeSetupView->disable();
}