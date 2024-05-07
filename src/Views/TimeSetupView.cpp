#include "Views/TimeSetupView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>
#include <RtcUtility.h>

#define TIME_EDIT_HOUR_COL_0 5U
#define TIME_EDIT_HOUR_COL_1 TIME_EDIT_HOUR_COL_0 + 1U
#define TIME_EDIT_MINUTES_COL_1 TIME_EDIT_HOUR_COL_0 + 4U
#define TIME_EDIT_ROW 1U

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
        m_pLcd->blink();
    }
}

void TimeSetupView::disable()
{
    m_pLcd->noBlink();
    enabled = false;
}

void TimeSetupView::setState(const TimeSetupViewIf::TimeSetupViewState state)
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

        m_pLcd->setCursor(TIME_EDIT_HOUR_COL_0, TIME_EDIT_ROW);
        m_pLcd->write(timeString);

        if (SETUP_HOURS == m_State)
        {
            m_pLcd->setCursor(TIME_EDIT_HOUR_COL_0 - 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(TIME_EDIT_MINUTES_COL_1 + 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));
            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(TIME_EDIT_HOUR_COL_1, TIME_EDIT_ROW);
        }
        else if (SETUP_MINUTES == m_State)
        {
            m_pLcd->setCursor(TIME_EDIT_MINUTES_COL_1 + 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(TIME_EDIT_HOUR_COL_0 - 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));
            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(TIME_EDIT_MINUTES_COL_1, TIME_EDIT_ROW);
        }
    }
}