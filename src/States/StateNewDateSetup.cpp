#include "States/StateNewDateSetup.hpp"
#include "ViewIf.hpp"

StateNewDateSetup StateNewDateSetup::m_Instance;

uint16_t StateNewDateSetup::m_Year = 2024U;
uint8_t StateNewDateSetup::m_Month = 1U;
uint8_t StateNewDateSetup::m_Day = 1U;

StateBase *StateNewDateSetup::getInstance()
{
    return &m_Instance;
}

StateNewDateSetup::StateNewDateSetup()
{
}

void StateNewDateSetup::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateNewDateSetup::enter()
{
    m_pDataSetupView->enable();
}

void StateNewDateSetup::exit()
{
    m_pDataSetupView->disable();
}