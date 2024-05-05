#include "Views/DateSetupView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

DateSetupView *DateSetupView::m_pInstance = nullptr;

DateSetupView *DateSetupView::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new DateSetupView();
    }
    return m_pInstance;
}

DateSetupView::DateSetupView()
    : m_State(DateSetupViewIf::DateSetupViewState::SETUP_DAYS), m_Year(0U), m_Month(0U), m_Day(0U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void DateSetupView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void DateSetupView::disable()
{
    enabled = false;
}

void DateSetupView::setState(const DateSetupViewIf::DateSetupViewState state)
{
    m_State = state;
}

DateSetupViewIf::DateSetupViewState DateSetupView::getState() const
{
    return m_State;
}

void DateSetupView::putYear(const uint16_t year)
{
}

void DateSetupView::putMonth(const uint8_t month)
{
}

void DateSetupView::putDay(const uint8_t day)
{
}

void DateSetupView::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(0, 0);
        m_pLcd->write("Set date");
    }
}

void DateSetupView::onRunCallback()
{
    DateSetupView::getInstance()->update();
}