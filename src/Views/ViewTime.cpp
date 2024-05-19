#include <LiquidCrystal.h>
#include <stdint.h>
#include "Views/ViewTime.hpp"
#include "ModuleConfig.hpp"
#include "Model/DateTime.hpp"
#include "SerialPrintAssert.h"

ViewTime *ViewTime::m_Instance = nullptr;

ViewTime *ViewTime::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new ViewTime();
    }

    return m_Instance;
}

ViewTime::ViewTime()
{
    setInterval(LCD_TIME_VIEW_UPDATE_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

uint8_t ViewTime::getViewId() const
{
    return VIEW_ID_TIME_VIEW;
}

void ViewTime::enable()
{
    RUNTIME_PTR_CHECK(m_pLcd);
    enabled = true;
    m_pLcd->clear();
}

void ViewTime::disable()
{
    enabled = false;
}

void ViewTime::onRunCallback()
{
    m_Instance->update();
}

void ViewTime::update()
{
    const DateTime now = m_pModel->getDateTime();
    if (now.isValid())
    {
        char datestring[20];

        m_pLcd->setCursor(0, 1);
        snprintf_P(datestring,
                   countof(datestring),
                   PSTR("%04u/%02u/%02u"),
                   now.getYear(),
                   now.getMonth(),
                   now.getDay());

        m_pLcd->write(datestring);

        m_pLcd->setCursor(0, 0);
        snprintf_P(datestring,
                   countof(datestring),
                   PSTR("%02u:%02u:%02u"),
                   now.getHour(),
                   now.getMinute(),
                   now.getSecond());

        m_pLcd->write(datestring);
    }
    else
    {
        m_pLcd->setCursor(0, 0);
        m_pLcd->write("No battery!");
    }
}
