#include <LiquidCrystal.h>
#include <stdint.h>

#include "Views/TimeView.hpp"
#include "ModuleConfig.hpp"

TimeView *TimeView::m_Instance = nullptr;

TimeView *TimeView::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new TimeView();
    }

    return m_Instance;
}

TimeView::TimeView()
{
    setInterval(LCD_TIME_VIEW_UPDATE_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

uint8_t TimeView::getViewid() const
{
    return VIEW_ID_TIME_VIEW;
}

void TimeView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void TimeView::disable()
{
    enabled = false;
}

void TimeView::onRunCallback()
{
    m_Instance->update();
}

void TimeView::update()
{
    if (nullptr != m_pLcd)
    {
        if (nullptr != m_Rtc)
        {
            const RtcDateTime now = m_Rtc->GetDateTime();
            if (now.IsValid())
            {
                char datestring[20];

                m_pLcd->setCursor(0, 1);
                snprintf_P(datestring,
                           countof(datestring),
                           PSTR("%04u/%02u/%02u"),
                           now.Year(),
                           now.Month(),
                           now.Day());

                m_pLcd->write(datestring);

                m_pLcd->setCursor(0, 0);
                snprintf_P(datestring,
                           countof(datestring),
                           PSTR("%02u:%02u:%02u"),
                           now.Hour(),
                           now.Minute(),
                           now.Second());

                m_pLcd->write(datestring);
            }
            else
            {
                m_pLcd->setCursor(0, 0);
                m_pLcd->write("Bad battery!!!");
            }
        }
        else
        {
            m_pLcd->setCursor(0, 0);
            m_pLcd->write("NO RTC obj!");
        }
    }
}