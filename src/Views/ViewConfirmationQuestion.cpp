#include <LiquidCrystal.h>

#include "Views/ViewConfirmationQuestion.hpp"
#include "ModuleConfig.hpp"

#define STR_ACCEPT "Accept?"
#define STR_YES "Yes?"
#define STR_NO "No?"

ViewConfirmationQuestion *ViewConfirmationQuestion::m_Instance = nullptr;

ViewConfirmationQuestion *ViewConfirmationQuestion::getInstance()
{
    if (nullptr == m_Instance)
    {
        m_Instance = new ViewConfirmationQuestion();
    }
    return m_Instance;
}

ViewConfirmationQuestion::ViewConfirmationQuestion()
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t ViewConfirmationQuestion::getViewid() const
{
    return VIEW_ID_CONFIRMATION_VIEW;
}

void ViewConfirmationQuestion::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void ViewConfirmationQuestion::disable()
{
    enabled = false;
}

void ViewConfirmationQuestion::update()
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

void ViewConfirmationQuestion::onRunCallback()
{
    getInstance()->update();
}