#include "Views/AlarmsStatusView.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

static const char *ALARMS_CAPTION = "ALARM:\0";
static const char *ALAMRS_COUNTER_CAPTION = "/8\0";

#define ALARMS_CAPTION_COL 2
#define ALARM_ID_CHANGE_CHAR_COL ALARMS_CAPTION_COL + 7
#define ALARM_ID_DIGIT_COL ALARMS_CAPTION_COL + 8
#define ALARM_STATUS_COL ALARMS_CAPTION_COL + 12

#define ALARMS_CAPTIONS_ROW 1

AlarmsStatusView *AlarmsStatusView::m_pInstance = nullptr;

AlarmsStatusView *AlarmsStatusView::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new AlarmsStatusView();
    }
    return m_pInstance;
}

AlarmsStatusView::AlarmsStatusView()
    : m_AlarmId(1U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

uint8_t AlarmsStatusView::getViewid() const
{
    return VIEW_ID_ALARMS_STATUS_VIEW;
}

void AlarmsStatusView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
        m_pLcd->blink();
    }
}

void AlarmsStatusView::disable()
{
    enabled = false;
    if (nullptr != m_pLcd)
    {
        m_pLcd->noBlink();
    }
}

void AlarmsStatusView::update()
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
        snprintf_P(alarmIdString, countof(alarmIdString), PSTR("%01u"), m_AlarmId);

        m_pLcd->setCursor(ALARM_ID_DIGIT_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(alarmIdString);
        m_pLcd->write(ALAMRS_COUNTER_CAPTION);

        m_pLcd->setCursor(ALARM_STATUS_COL, ALARMS_CAPTIONS_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_ALARM_ENABLED_INDEX));

        m_pLcd->setCursor(ALARM_ID_DIGIT_COL, ALARMS_CAPTIONS_ROW);
    }
}

void AlarmsStatusView::setAlarmToDisplay(const uint8_t alarmId)
{
    m_AlarmId = alarmId;
}

void AlarmsStatusView::onRunCallback()
{
    AlarmsStatusView::getInstance()->update();
}