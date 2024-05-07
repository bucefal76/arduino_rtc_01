#include "Views/DateSetupView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

#define YEAR_EDIT_COL 2U
#define MONTH_EDIT_COL 8U
#define DAY_EDIT_COL 12U

#define DATE_EDIT_ROW 1U

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
    : m_State(DateSetupViewIf::DateSetupViewState::SETUP_DAY), m_Year(0U), m_Month(0U), m_Day(0U)
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
        m_pLcd->blink();
    }
}

void DateSetupView::disable()
{
    enabled = false;
    if (nullptr != m_pLcd)
    {
        m_pLcd->noBlink();
    }
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
    m_Year = year;
}

void DateSetupView::putMonth(const uint8_t month)
{
    m_Month = month;
}

void DateSetupView::putDay(const uint8_t day)
{
    m_Day = day;
}

void DateSetupView::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(YEAR_EDIT_COL, DATE_EDIT_ROW);

        char datestring[20];

        snprintf_P(datestring,
                   countof(datestring),
                   PSTR("%04u  %02u  %02u"),
                   m_Year,
                   m_Month,
                   m_Day);

        m_pLcd->write(datestring);

        switch (m_State)
        {
        case DateSetupViewIf::DateSetupViewState::SETUP_YEAR:
        {
            m_pLcd->setCursor(YEAR_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

            m_pLcd->setCursor(MONTH_EDIT_COL + 2, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

            m_pLcd->setCursor(DAY_EDIT_COL + 2, DATE_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(YEAR_EDIT_COL + 3, DATE_EDIT_ROW);
        }
        break;
        case DateSetupViewIf::DateSetupViewState::SETUP_MONTH:
        {
            m_pLcd->setCursor(MONTH_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(YEAR_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

            m_pLcd->setCursor(DAY_EDIT_COL + 2, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

            m_pLcd->setCursor(BUTTON_NEXT_IO_LINE, DATE_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(MONTH_EDIT_COL + 1, DATE_EDIT_ROW);
        }
        break;
        case DateSetupViewIf::DateSetupViewState::SETUP_DAY:
        {
            m_pLcd->setCursor(DAY_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

            m_pLcd->setCursor(MONTH_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

            m_pLcd->setCursor(DAY_EDIT_COL + 2, DATE_EDIT_ROW);
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

            m_pLcd->setCursor(YEAR_EDIT_COL - 1, DATE_EDIT_ROW);
            m_pLcd->write(" ");

            m_pLcd->setCursor(DAY_EDIT_COL + 1, DATE_EDIT_ROW);
        }

        default:
            break;
        }
    }
}

void DateSetupView::onRunCallback()
{
    DateSetupView::getInstance()->update();
}