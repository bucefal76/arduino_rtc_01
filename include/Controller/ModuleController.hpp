#ifndef MODULE_CONTROLLER_HPP
#define MODULE_CONTROLLER_HPP

#include <Arduino.h>
#include <Thread.h>
#include <RtcDS1302.h>

#include "ModuleConfig.hpp"

class StateBase;
class KeyboardControllerIf;
class ViewIf;
class ExtendedViewIf;
class MenuViewIf;
class TimeSetupViewIf;
class DateSetupViewIf;
class ModuleModelIf;
class ModuleModelStateIf;

/*
    The goal is to develop a clock application based on the Controller-View architectural pattern.
    The Views are responsible for showing messages on the LCD, and the KeyboardController (refer to KeyboardControllerIf) interprets pressed keys.
    The ModuleController manages the flow of control. To simplify things further (or make it more complex),
    the ModuleController uses a basic state machine under the hood for flow control.
*/

class ModuleController : public Thread
{
public:
    static ModuleController *getInstance();

    /// @brief Use this method on the setup() to set the pointer to the keyboard controller.
    void setKeyboardController(KeyboardControllerIf *keyboardController);
    /// @brief Add views to the list of views managed by the Controller.
    /// @param pView
    void addView(ViewIf *pView);
    /// @brief Add extended views to the list of views managed by the Controller.
    void addExtendedView(const uint8_t viewId, ExtendedViewIf *pExtendedView);
    /// @brief Set Model that represents RTC, interface to do changes on the RTC.
    void setModel(ModuleModelIf *pModel);
    /// @brief   Set Model that represents RTC, interface to get state of the model.
    void setModelState(ModuleModelStateIf *pModelStatus);

private:
    ModuleController();

    void update();

    static void onRunCallback();

    /// @brief Pointer to the keyboard controller.
    KeyboardControllerIf *m_KeyboardController;
    /// @brief Instance of this object (ModuleController class).
    static ModuleController *m_pInstance;
};

#endif