#include "Views/ViewAlarmsStatus.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

static const char *ALARMS_CAPTION = "LINE:\0";
static const char *ALARMS_COUNTER_CAPTION = "/8\0";

#define ALARMS_CAPTION_COL 2
#define ALARM_ID_CHANGE_CHAR_COL ALARMS_CAPTION_COL + 7
#define ALARM_ID_DIGIT_COL ALARMS_CAPTION_COL + 8
#define ALARM_STATUS_COL ALARMS_CAPTION_COL + 12

#define ALARMS_CAPTIONS_ROW 1

ViewAlarmsStatus *ViewAlarmsStatus::m_pInstance = nullptr;

ViewAlarmsStatus *ViewAlarmsStatus::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ViewAlarmsStatus();
    }
    return m_pInstance;
}

ViewAlarmsStatus::ViewAlarmsStatus()
    : m_AlarmLineId(1U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t ViewAlarmsStatus::getViewId() const
{
    return VIEW_ID_LINES_STATUS_VIEW;
}

void ViewAlarmsStatus::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
        m_pLcd->blink();
    }
}

void ViewAlarmsStatus::disable()
{
    enabled = false;
    if (nullptr != m_pLcd)
    {
        m_pLcd->noBlink();
    }
}

void ViewAlarmsStatus::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

        m_pLcd->setCursor(ALARMS_CAPTION_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(ALARMS_CAPTION);

        m_pLcd->setCursor(ALARM_ID_CHANGE_CHAR_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

        char alarmIdString[2];
        snprintf_P(alarmIdString, countof(alarmIdString), PSTR("%01u"), m_AlarmLineId);

        m_pLcd->setCursor(ALARM_ID_DIGIT_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(alarmIdString);
        m_pLcd->write(ALARMS_COUNTER_CAPTION);

        m_pLcd->setCursor(ALARM_STATUS_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

        if (m_pModel->isAlarmLineArmed(m_AlarmLineId))
        {
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_ALARM_ENABLED_INDEX));
        }
        else
        {
            m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_ALARM_DISABLED_INDEX));
        }

        m_pLcd->setCursor(ALARM_ID_DIGIT_COL, ALARMS_CAPTIONS_ROW);
    }
}

void ViewAlarmsStatus::setAlarmIdToDisplay(const uint8_t alarmId)
{
    m_AlarmLineId = alarmId;
}

void ViewAlarmsStatus::onRunCallback()
{
    ViewAlarmsStatus::getInstance()->update();
}