#include "Views/ViewAlarmSettings.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

#define LINE_CAPTION "LINE:\0"

ViewAlarmSettings *ViewAlarmSettings::m_pInstance = nullptr;

ViewAlarmSettings *ViewAlarmSettings::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ViewAlarmSettings();
    }
    return m_pInstance;
}

ViewAlarmSettings::ViewAlarmSettings()
    : m_AlarmId(8U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t ViewAlarmSettings::getViewId() const
{
    return VIEW_ID_LINE_SETTINGS_VIEW;
}

void ViewAlarmSettings::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
        m_pLcd->blink();
    }
}

void ViewAlarmSettings::disable()
{
    enabled = false;
    if (nullptr != m_pLcd)
    {
        m_pLcd->noBlink();
    }
}

void ViewAlarmSettings::setAlarmToDisplay(const uint8_t alarmId)
{
    m_AlarmId = alarmId;
}

void ViewAlarmSettings::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(0, 0);
        m_pLcd->write(LINE_CAPTION);
    }
}

void ViewAlarmSettings::onRunCallback()
{
    ViewAlarmSettings::getInstance()->update();
}