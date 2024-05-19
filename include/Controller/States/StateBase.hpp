#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "KeyboardControllerIf.hpp"
#include <RtcDS1302.h>
#include <map>

class ViewIf;
class ExtendedViewIf;
class ViewMenuIf;
class ViewTimeSetupIf;
class ViewDateSetupIf;
class ModuleModelIf;
class ModuleModelStateIf;

/*
    BaseState is an abstract class that serves as the root class for several derived classes,
    which implement application behavior. These derived classes share some common functionality and data,
    such as pointers to views, and are also required to implement certain virtual methods.
    The BaseState class exists for these two specific reasons.

    The BaseState is used to create a State Machine pattern that is not based on the G.O.F pattern.
    The state machine implementation has a few simplifications and rules.
    Firstly, all machine states must be derived from StateBase.
    Secondly, all derived classes are singletons and global in themselves to save memory resources.
    Finally, to move from one state to another, the transitToState method should be used, and only this method.

    Call to transitToState will cause execution of the exit() method at the old state and then execution
    of the enter() at the new state.
*/

class StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);
    /// @brief  State machine needs to have an access to the views objects, the special one.
    static void addExtendedView(const uint8_t viewId, ExtendedViewIf *pExtendedView);
    /// @brief State machine needs to have an access to the views objects, the typical one.
    static void addView(ViewIf *pView);
    /// @brief Set pointer to the Model that represents RTC, interface  to do changes at the model.
    static void setModel(ModuleModelIf *pModel);
    /// @brief Set pointer to the Model that represents RTC, interface to get state of the model.
    static void setModelState(ModuleModelStateIf *pModelState);
    /// @brief Get the current state of the controller.
    static StateBase *getCurrentState();
    /// @brief Set current state in the controller.
    static void setCurrentState(StateBase *state);

protected:
    /// @brief Use this method to switch state machine to next state
    /// @param pNexState
    void transitToState(StateBase *pNexState);
    /// @brief When transitioning to a new state, a method is automatically called by transitToNextState.
    virtual void enter() = 0;
    /// @brief When transitioning to a new state, a method is automatically called by transitToNextState.
    virtual void exit() = 0;
    /// @brief Current state of the state machine.
    static StateBase *m_pCurrentState;
    /// Returns pointer to the standard view bny given ID, see ModuleConfig.hpp for views ID.
    ViewIf *getView(const uint8_t viewId) const;
    /// Returns pointer to the extended view bny given ID, see ModuleConfig.hpp for views ID.
    ExtendedViewIf *getExtendedView(const uint8_t viewId) const;
    /// @brief Map with pointers to the standard views.
    static std::map<uint8_t, ViewIf *> m_Views;
    /// @brief Map with pointers to the extended views.
    static std::map<uint8_t, ExtendedViewIf *> m_ExtendedViews;
    /// @brief Pointer to the model of the RTC. Interface to do changes.
    static ModuleModelIf *m_pModel;
    /// @brief Pointer to the model of the RTC. Interface to get state only.
    static ModuleModelStateIf *m_pModelState;
};

#endif