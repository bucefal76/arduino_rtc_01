#include "Views/AlarmsStatusView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

AlarmsStatusView *AlarmsStatusView::m_pInstance = nullptr;

AlarmsStatusView *AlarmsStatusView::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new AlarmsStatusView();
    }
    return m_pInstance;
}

AlarmsStatusView::AlarmsStatusView()
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t AlarmsStatusView::getViewid() const
{
    return VIEW_ID_ALARMS_STATUS_VIEW;
}

void AlarmsStatusView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
        m_pLcd->blink();
    }
}

void AlarmsStatusView::disable()
{
    enabled = false;
    if (nullptr != m_pLcd)
    {
        m_pLcd->noBlink();
    }
}

void AlarmsStatusView::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(0, 0);
        m_pLcd->write("Now display alarms");
    }
}

void AlarmsStatusView::onRunCallback()
{
    AlarmsStatusView::getInstance()->update();
}