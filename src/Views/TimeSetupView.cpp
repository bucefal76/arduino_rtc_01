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
    : m_Hours(0U), m_Minutes(0U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void TimeSetupView::setLcd(LiquidCrystal *pLcd)
{
    m_pLcd = pLcd;
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

void TimeSetupView::putHours(const uint8_t hour)
{
}

void TimeSetupView::putMinutes(const uint8_t hour)
{
}

void TimeSetupView::onRunCallback()
{
    m_pInstance->update();
}

void TimeSetupView::update()
{
    if (nullptr != m_pLcd)
    {
        char timeString[5];
        snprintf_P(timeString,
                   countof(timeString),
                   PSTR("%02u:/%02u"),
                   m_Hours,
                   m_Minutes);

        m_pLcd->setCursor(10, 1);
        m_pLcd->write(timeString);
    }
}