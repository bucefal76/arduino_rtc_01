#include "States/StateNewDateSetup.hpp"
#include "States/StateNewDateConfirmation.hpp"
#include "ViewIf.hpp"
#include "DateSetupViewIf.hpp"
#include "ModuleConfig.hpp"

#define YEAR_MAX_VALUE 2035U
#define YEAR_MIN_VALUE 2020U
#define MONTH_MAX_VALUE 12U
#define MONTH_MIN_VALUE 1U
#define DAY_MIN_VALUE 1U

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
    const DateSetupViewIf::DateSetupViewState currentlyInSetup = m_pExtendedDateSetupView->getState();

    switch (currentlyInSetup)
    {
    case DateSetupViewIf::DateSetupViewState::SETUP_YEAR:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Year++;
            if (m_Year > YEAR_MAX_VALUE)
            {
                m_Year = YEAR_MIN_VALUE;
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            m_Year--;
            if (m_Year < YEAR_MIN_VALUE)
            {
                m_Year = YEAR_MAX_VALUE;
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            m_pExtendedDateSetupView->setState(DateSetupViewIf::DateSetupViewState::SETUP_MONTH);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            trasitToState(StateNewDateConfirmation::getInstance());
        }

        break;
    }
    case DateSetupViewIf::DateSetupViewState::SETUP_MONTH:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            m_Month++;
            if (m_Month > MONTH_MAX_VALUE)
            {
                m_Month = MONTH_MIN_VALUE;
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            m_Month--;
            if (m_Month < MONTH_MIN_VALUE)
            {
                m_Month = MONTH_MAX_VALUE;
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            m_pExtendedDateSetupView->setState(DateSetupViewIf::DateSetupViewState::SETUP_DAY);
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            m_pExtendedDateSetupView->setState(DateSetupViewIf::DateSetupViewState::SETUP_YEAR);
        }
        break;
    }
    case DateSetupViewIf::DateSetupViewState::SETUP_DAY:
    {
        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_UP == button)
        {
            const uint8_t maxNumberOfDays = getNumberOfDays(m_Month, m_Year);

            m_Day++;
            if (m_Day > maxNumberOfDays)
            {
                m_Day = DAY_MIN_VALUE;
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_DOWN == button)
        {
            m_Day--;
            if (m_Day < DAY_MIN_VALUE)
            {
                m_Day = getNumberOfDays(m_Month, m_Year);
            }

            updateViewData();
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
        {
            trasitToState(StateNewDateConfirmation::getInstance());
        }
        else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
        {
            m_pExtendedDateSetupView->setState(DateSetupViewIf::DateSetupViewState::SETUP_MONTH);
        }
        break;
    }
    default:
        break;
    }
}
void StateNewDateSetup::enter()
{
    getView(VIEW_ID_DATE_SETUP_VIEW)->enable();

    m_pExtendedDateSetupView->setState(DateSetupViewIf::SETUP_YEAR);
    m_pExtendedDateSetupView->putDay(m_Day);
    m_pExtendedDateSetupView->putMonth(m_Month);
    m_pExtendedDateSetupView->putYear(m_Year);
}

void StateNewDateSetup::exit()
{
    getView(VIEW_ID_DATE_SETUP_VIEW)->disable();
}

void StateNewDateSetup::updateViewData() const
{
    m_pExtendedDateSetupView->putYear(m_Year);
    m_pExtendedDateSetupView->putMonth(m_Month);

    const uint8_t maxDaysInCurrentMonth = getNumberOfDays(m_Month, m_Year);

    if (maxDaysInCurrentMonth < m_Day)
    {
        m_Day = maxDaysInCurrentMonth;
    }
    m_pExtendedDateSetupView->putDay(m_Day);
}

uint8_t StateNewDateSetup::getNumberOfDays(const uint8_t month, const uint16_t year) const
{
    // With a help of the MS Coopilot :) :
    // As this is not my code I'm leaving here magic numbers...
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        // Months with 30 days
        return 30;
    }
    else if (month == 2)
    {
        // February: check for leap year
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        {
            return 29; // Leap year
        }
        else
        {
            return 28; // Non-leap year
        }
    }
    else
    {
        // Months with 31 days
        return 31;
    }
}