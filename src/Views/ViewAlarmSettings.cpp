#include "Views/ViewAlarmSettings.hpp"
#include "Model/DateTime.hpp"
#include "ModuleConfig.hpp"
#include <LiquidCrystal.h>

#define LINE_CAPTION "LINE:\0"
#define CYCLE_CAPTION " CYCLE:\0"

#define LINE_ALARM_ON_CHARACTER_POS 1U
#define LINE_ALARM_OFF_CHARACTER_POS 14U
#define LINE_ALARM_OFF_TIME_POS 9U
#define LINE_ALARM_ON_HOURS_CURSOR_POS 3U
#define LINE_ALARM_ON_MINUTES_CURSOR_POS 6U
#define LINE_ALARM_OFF_HOURS_CURSOR_POS 10U
#define LINE_ALARM_OFF_MINUTES_CURSOR_POS 13U
#define LINE_ALARM_ON_TIME_EDITED_POS 7U
#define LINE_ALARM_OFF_TIME_EDITED_POS 8U

#define LINE_CAPTION_COL 0U
#define LINE_CAPTION_ROW 0U
#define LINE_EDIT_ROW 1U

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
    : m_AlarmId(1U),
      m_CycleId(1U),
      m_pOnTimeHours(0U),
      m_pOnTimeMinutes(0U),
      m_pOffTimeHours(0U),
      m_pOffTimeMinutes(0U),
      m_State(ViewAlarmSettingsIf::SETUP_ON_HOURS)

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

void ViewAlarmSettings::setState(const ViewAlarmSettingsState newState)
{
    m_State = newState;
}

ViewAlarmSettingsIf::ViewAlarmSettingsState ViewAlarmSettings::getState() const
{
    return m_State;
}

void ViewAlarmSettings::setAlarmToDisplay(const uint8_t alarmId)
{
    m_AlarmId = alarmId;
}

void ViewAlarmSettings::setOnTimeToDisplay(const uint8_t hours, const uint8_t minutes)
{
    m_pOnTimeHours = hours;
    m_pOnTimeMinutes = minutes;
}

void ViewAlarmSettings::setOffTimeToDisplay(const uint8_t hours, const uint8_t minutes)
{
    m_pOffTimeHours = hours;
    m_pOffTimeMinutes = minutes;
}

void ViewAlarmSettings::update()
{
    if (nullptr != m_pLcd)
    {
        // LINE:
        m_pLcd->setCursor(LINE_CAPTION_COL, LINE_CAPTION_ROW);
        m_pLcd->write(LINE_CAPTION);
        m_pLcd->print(m_AlarmId);

        // CYCLE:
        m_pLcd->write(CYCLE_CAPTION);
        m_pLcd->print(m_CycleId);

        // <
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, LINE_EDIT_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));

        // _|
        m_pLcd->setCursor(LINE_ALARM_ON_CHARACTER_POS, LINE_EDIT_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_ALARM_ON_INDEX));

        char timeString[6];
        snprintf_P(timeString,
                   countof(timeString),
                   PSTR("%02u:%02u"),
                   m_pOnTimeHours,
                   m_pOnTimeMinutes);
        m_pLcd->write(timeString);

        m_pLcd->setCursor(LINE_ALARM_OFF_TIME_POS, LINE_EDIT_ROW);
        snprintf_P(timeString,
                   countof(timeString),
                   PSTR("%02u:%02u"),
                   m_pOffTimeHours,
                   m_pOffTimeMinutes);
        m_pLcd->write(timeString);

        //  |_
        m_pLcd->setCursor(LINE_ALARM_OFF_CHARACTER_POS, LINE_EDIT_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_ALARM_OFF_INDEX));

        //  >
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION, LINE_EDIT_ROW);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

        // /\ \/
        switch (m_State)
        {
        case ViewAlarmSettingsIf::SETUP_ON_HOURS:
        case ViewAlarmSettingsIf::SETUP_ON_MINUTES:
        {
            m_pLcd->setCursor(LINE_ALARM_OFF_TIME_EDITED_POS, LINE_EDIT_ROW);
            m_pLcd->write(" ");
            m_pLcd->setCursor(LINE_ALARM_ON_TIME_EDITED_POS, LINE_EDIT_ROW);
        }
        break;

        case ViewAlarmSettingsIf::SETUP_OFF_HOURS:
        case ViewAlarmSettingsIf::SETUP_OFF_MINUTES:
        {
            m_pLcd->setCursor(LINE_ALARM_ON_TIME_EDITED_POS, LINE_EDIT_ROW);
            m_pLcd->write(" ");
            m_pLcd->setCursor(LINE_ALARM_OFF_TIME_EDITED_POS, LINE_EDIT_ROW);
        }
        break;
        }

        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX));

        // Edit focus
        if (ViewAlarmSettingsIf::SETUP_ON_HOURS == m_State)
        {
            m_pLcd->setCursor(LINE_ALARM_ON_HOURS_CURSOR_POS, LINE_EDIT_ROW);
        }
        else if (ViewAlarmSettingsIf::SETUP_ON_MINUTES == m_State)
        {
            m_pLcd->setCursor(LINE_ALARM_ON_MINUTES_CURSOR_POS, LINE_EDIT_ROW);
        }
        else if (ViewAlarmSettingsIf::SETUP_OFF_HOURS == m_State)
        {
            m_pLcd->setCursor(LINE_ALARM_OFF_HOURS_CURSOR_POS, LINE_EDIT_ROW);
        }
        else
        {
            m_pLcd->setCursor(LINE_ALARM_OFF_MINUTES_CURSOR_POS, LINE_EDIT_ROW);
        }
    }
}

void ViewAlarmSettings::onRunCallback()
{
    ViewAlarmSettings::getInstance()->update();
}