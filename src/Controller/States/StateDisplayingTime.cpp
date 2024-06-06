#include "Controller/States/StateDisplayingTime.hpp"
#include "Controller/States/StateDisplayingMenuSetTime.hpp"
#include "Model/DateTime.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"
#include "ModuleConfig.hpp"
#include "ViewIf.hpp"
#include "ViewMenuIf.hpp"

#include <Arduino.h>

StateDisplayingTime StateDisplayingTime::m_Instance;

StateBase *StateDisplayingTime::getInstance()
{
    return &m_Instance;
}

StateDisplayingTime::StateDisplayingTime()
{
}

void StateDisplayingTime::processButton(const KeyboardControllerIf::ButtonCode button)
{
    transitToState(StateDisplayingMenuSetTime::getInstance());
}

void StateDisplayingTime::update()
{
    uint8_t controlWord = m_pModel->getIoLineControlWord();

    const DateTime currentTime = m_pModelState->getDateTime();

    for (uint8_t alarmLineIt = 0; alarmLineIt < ALARMS_NO_OF_LINES; alarmLineIt++)
    {
        if (m_pModelState->isAlarmLineArmed(alarmLineIt))
        {
            for (uint8_t alarmCycleIt = 0; alarmCycleIt < ALARMS_NO_OF_CYCLES_PER_LINE; alarmCycleIt++)
            {
                const AlarmLineFlagTime onTime = m_pModelState->getAlarmLineOnTime(alarmLineIt, alarmCycleIt);

                if ((currentTime.getHour() == onTime.m_Hours) && (currentTime.getMinute() == onTime.m_Minutes))
                {
                    controlWord = controlWord | (1U << alarmLineIt);
                }

                const AlarmLineFlagTime offTime = m_pModelState->getAlarmLineOffTime(alarmLineIt, alarmCycleIt);

                if ((currentTime.getHour() == offTime.m_Hours) && (currentTime.getMinute() == offTime.m_Minutes))
                {
                    controlWord = controlWord & ~(1U << alarmLineIt);
                }
            }
        }
    }

    m_pModel->setIoLineControlWord(controlWord);
}

void StateDisplayingTime::enter()
{
    getView(VIEW_ID_TIME_VIEW)->enable();
}

void StateDisplayingTime::exit()
{
    getView(VIEW_ID_TIME_VIEW)->disable();
}