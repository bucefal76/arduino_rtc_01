#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "KeyboardControllerIf.hpp"
#include <RtcDS1302.h>
#include <map>

class ViewIf;
class MenuViewIf;
class TimeSetupViewIf;
class DateSetupViewIf;
class ModuleModelIf;

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
    /// @brief  State machine needs to have an access to the views objects, the special one.
    ///         Not sure how to refactor it to more generic interface.
    static void setExtendedViews(MenuViewIf *extendedMenuView,
                                 TimeSetupViewIf *extendedTimeSetupView,
                                 DateSetupViewIf *extendedDateSetupView);
    /// @brief State machine needs to have an access to the views objects, the typical one.
    static void addView(ViewIf *pView);
    /// @brief Set pointer to the Model that represents RTC.
    static void setModel(ModuleModelIf *pModel);
    /// @brief Get the current state of the controller.
    static StateBase *getCurrentState();
    /// @brief Set current state in the controller.
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
    /// Returns pointer to the view bny given ID, see ModuleConfig.hpp for views ID.
    ViewIf *getView(const uint8_t viewId) const;
    /// @brief Pointers to the Manu view, for some more than one pointer for one object.
    /// Because we may have different interfaces for diferent purpose for single view object (see Interface Soup antipattern)
    /// Adaptive Code: Agile coding with design patterns and SOLID principles by Gary Mclean Hall.
    static MenuViewIf *m_ExtendedMenuView;
    static TimeSetupViewIf *m_pExtendedTimeSetupView;
    static DateSetupViewIf *m_pExtendedDateSetupView;
    /// @brief Map with pointer to the standard views.
    static std::map<uint8_t, ViewIf *> m_Views;
    /// @brief  Pointer to the model of the RTC.
    static ModuleModelIf *m_pModel;
};

#endif