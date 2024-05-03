#include "Views/TimeSetupView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>
#include <RtcUtility.h>

TimeSetupView *TimeSetupView::m_pInstance = nullptr;

TimeSetupView *TimeSetupView::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new TimeSetupView();
    }
    return m_pInstance;
}

TimeSetupView::TimeSetupView()
    : m_Hours(0U), m_Minutes(0U), m_State(TimeSetupViewIf::TimeSetupViewState::SETUP_HOURS)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void TimeSetupView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void TimeSetupView::disable()
{
    enabled = false;
}

void TimeSetupView::setState(TimeSetupViewIf::TimeSetupViewState state)
{
    m_State = state;
}

TimeSetupViewIf::TimeSetupViewState TimeSetupView::getState() const
{
    return m_State;
}

void TimeSetupView::putHours(const uint8_t hours)
{
    m_Hours = hours;
}

void TimeSetupView::putMinutes(const uint8_t minutes)
{
    m_Minutes = minutes;
}

void TimeSetupView::onRunCallback()
{
    m_pInstance->update();
}

void TimeSetupView::update()
{
    if (nullptr != m_pLcd)
    {
        char timeString[6];
        snprintf_P(timeString,
                   countof(timeString),
                   PSTR("%02u:%02u"),
                   m_Hours,
                   m_Minutes);

        m_pLcd->setCursor(5, 1);
        m_pLcd->write(timeString);
    }
}