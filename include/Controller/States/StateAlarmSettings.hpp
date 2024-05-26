#ifndef STATE_ALARM_SETTINGS_HPP
#define STATE_ALARM_SETTINGS_HPP

#include "StateBase.hpp"
#include "Model/TimeInvariant.hpp"

class StateAlarmSettings : public StateBase
{
public:
    /// @brief See StateBase
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);
    /// @brief Returns pointer to the instance of this class.
    static StateBase *getInstance();
    /// @brief Set ID of rhe current line to edit.
    static void setCurrentLineId(const uint8_t currentLineId);

private:
    virtual void enter();
    virtual void exit();

    /// @brief Instance of this class.
    static StateAlarmSettings m_Instance;
    /// @brief  Id of the currently edited line.
    static uint8_t m_CurrentLineId;
    /// @brief  Id of the currently edited cycle for selected control line.
    uint8_t m_CurrentCycleId;

protected:
    StateAlarmSettings();
    /// @brief Table with On times for susequential ON/OFF cycles.
    TimeInvariant m_OnTime[ALARMS_NO_OF_CYCLES_PER_LINE];
    /// @brief Table with OFF times for susequential ON/OFF cycles.
    TimeInvariant m_OffTime[ALARMS_NO_OF_CYCLES_PER_LINE];
};

#endif
