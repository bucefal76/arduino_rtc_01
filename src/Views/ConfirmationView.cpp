#include <LiquidCrystal.h>

#include "Views/ConfirmationView.hpp"
#include "ModuleConfig.hpp"

#define STR_ACCEPT "Accept?"
#define STR_YES "Yes?"
#define STR_NO "No?"

ConfirmationView *ConfirmationView::m_Instance = nullptr;

ConfirmationView *ConfirmationView::getInstance()
{
    if (nullptr == m_Instance)
    {
        m_Instance = new ConfirmationView();
    }
    return m_Instance;
}

ConfirmationView::ConfirmationView()
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void ConfirmationView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void ConfirmationView::disable()
{
    enabled = false;
}

void ConfirmationView::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(5, 0);
        m_pLcd->write(STR_ACCEPT);

        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, 1U);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));
        m_pLcd->write(STR_NO);

        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION - sizeof(STR_YES), 1U);
        m_pLcd->write(STR_YES);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));
    }
}

void ConfirmationView::onRunCallback()
{
    getInstance()->update();
}