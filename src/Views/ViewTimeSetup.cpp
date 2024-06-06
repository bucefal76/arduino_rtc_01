#include "Views/ViewTimeSetup.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>
#include <RtcUtility.h>

#define TIME_EDIT_HOUR_COL_0 5U
#define TIME_EDIT_HOUR_COL_1 TIME_EDIT_HOUR_COL_0 + 1U
#define TIME_EDIT_MINUTES_COL_1 TIME_EDIT_HOUR_COL_0 + 4U
#define TIME_EDIT_ROW 1U

ViewTimeSetup *ViewTimeSetup::m_pInstance = nullptr;

ViewTimeSetup *ViewTimeSetup::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ViewTimeSetup();
    }
    return m_pInstance;
}

ViewTimeSetup::ViewTimeSetup()
    : m_Hours(0U), m_Minutes(0U), m_State(ViewTimeSetupIf::ViewTimeSetupState::SETUP_HOURS)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t ViewTimeSetup::getViewId() const
{
    return VIEW_ID_TIME_SETUP_VIEW;
}

void ViewTimeSetup::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
        m_pLcd->blink();
    }
}

void ViewTimeSetup::disable()
{
    m_pLcd->noBlink();
    enabled = false;
}

void ViewTimeSetup::setState(const ViewTimeSetupIf::ViewTimeSetupState state)
{
    m_State = state;
}

ViewTimeSetupIf::ViewTimeSetupState ViewTimeSetup::getState() const
{
    return m_State;
}

void ViewTimeSetup::putHours(const uint8_t hours)
{
    m_Hours = hours;
}

void ViewTimeSetup::putMinutes(const uint8_t minutes)
{
    m_Minutes = minutes;
}

void ViewTimeSetup::onRunCallback()
{
    m_pInstance->update();
}

void ViewTimeSetup::update()
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

            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COL_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));
            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COL_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(TIME_EDIT_HOUR_COL_1, TIME_EDIT_ROW);
        }
        else if (SETUP_MINUTES == m_State)
        {
            m_pLcd->setCursor(TIME_EDIT_MINUTES_COL_1 + 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(TIME_EDIT_HOUR_COL_0 - 1U, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COL_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));
            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COL_POSITION, TIME_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(TIME_EDIT_MINUTES_COL_1, TIME_EDIT_ROW);
        }
    }
}