#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "KeyboardControllerIf.hpp"
#include <RtcDS1302.h>

class ViewIf;
class MenuViewIf;
class TimeSetupViewIf;
class DateSetupViewIf;

/*
    BaseState is an abstract class that serves as the root class for several derived classes,
    which implement application behavior. These derived classes share some common functionality and data,
    such as pointers to views, and are also required to implement certain virtual methods.
    The BaseState class exists for these two specific reasons.

    The BaseState is used to create a State Machine pattern that is not based on the G.O.F pattern.
    The state machine implementation has a few simplifications and rules.
    Firstly, all machine states must be derived from StateBase.
    Secondly, all derived classes are singletons and global in themselves to save memory resources.
    Finally, to move from one state to another, the trasitToState method should be used, and only this method.

    Call to trasitToState will cause execution of the exit() method at the old state and then execution
    of the enter() at the new state.
*/

class StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);
    /// @brief  State machine needs to have an access to the views objects:
    static void setViews(ViewIf *timeView,
                         ViewIf *menuView,
                         MenuViewIf *extendedMenuView,
                         ViewIf *timeSetupView,
                         TimeSetupViewIf *extendedTimeSetupView,
                         ViewIf *confirmationView,
                         ViewIf *dataSetupView,
                         DateSetupViewIf *extendedDateSetupView);
    /// @brief State machine needs to have access to the RTC driver.
    static void setRtc(RtcDS1302<ThreeWire> *rtc);

    static StateBase *getCurrentState();
    static void setCurrentState(StateBase *state);

protected:
    /// @brief Use this methid to switch state machine to next state
    /// @param pNexState
    void trasitToState(StateBase *pNexState);
    /// @brief When transitioning to a new state, a method is automatically called by transitToNextState.
    virtual void enter() = 0;
    /// @brief When transitioning to a new state, a method is automatically called by transitToNextState.
    virtual void exit() = 0;
    /// @brief Current state of the state machine.
    static StateBase *m_pCurrentState;
    /// @brief Pointer to the time display view.
    static ViewIf *m_TimeView;
    /// @brief Pointers to the Manu view, twwo as we have
    /// two different interfaces (see Interface Soup antipattern)
    /// Adaptive Code: Agile coding with design patterns and SOLID principles by Gary Mclean Hall.
    static ViewIf *m_MenuView;
    static MenuViewIf *m_ExtendedMenuView;
    static ViewIf *m_pTimeSetupView;
    static TimeSetupViewIf *m_pExtendedTimeSetupView;
    static ViewIf *m_pConfirmationView;
    static ViewIf *m_pDataSetupView;
    static DateSetupViewIf *m_pExtendedDateSetupView;
    /// @brief Pointer to the RTC driver.
    static RtcDS1302<ThreeWire> *m_pRtc;
};

#endif