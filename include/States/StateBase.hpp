#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "KeyboardControllerIf.hpp"
#include <RtcDS1302.h>

class ViewIf;
class MenuViewIf;
class TimeSetupViewIf;

/*
    BaseState is an abstract class that serves as the root class for several derived classes,
    which implement application behavior. These derived classes share some common functionality and data,
    such as pointers to views, and are also required to implement certain virtual methods.
    The BaseState class exists for these two specific reasons.

    The BaseState is used to build a kind of State Machine pattern (not a G.O.F one).
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
                         ViewIf *confirmationView);
    /// @brief State machine needs to have access to the RTC driver.
    static void setRtc(RtcDS1302<ThreeWire> *rtc);

    static StateBase *getCurrentState();
    static void setCurrentState(StateBase *state);

protected:
    /// @brief Use this methid to switch state machine to next state
    /// @param pNexState
    void trasitToNextState(StateBase *pNexState);
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
    /// @brief Pointer to the RTC driver.
    static RtcDS1302<ThreeWire> *m_pRtc;
};

#endif