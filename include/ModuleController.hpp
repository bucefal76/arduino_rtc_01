#ifndef MODULE_CONTROLLER_HPP
#define MODULE_CONTROLLER_HPP

#include <Arduino.h>
#include <Thread.h>
#include <RtcDS1302.h>

#include "ModuleConfig.hpp"

class StateBase;
class KeyboardControllerIf;
class ViewIf;
class MenuViewIf;
class TimeSetupViewIf;

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

    ModuleController();

    /// @brief Use this method on the setup() to set the pointer to the keyboard controller.
    void setKeyboardController(KeyboardControllerIf *keyboardController);
    /// @brief  Use this method on the setup() to set the pointer to all views used by the application.
    void setViews(ViewIf *timeView,
                  ViewIf *menuView,
                  MenuViewIf *extendedMenuView,
                  ViewIf *timeSetupView,
                  TimeSetupViewIf *extendedTimeSetupView,
                  ViewIf *confirmationView,
                  ViewIf *dataSetupView);
    /// @brief  Use this method on setup() to set the pointer to the Real Time Clock driver.
    void setRtc(RtcDS1302<ThreeWire> *rtc);

private:
    void update();

    static void onRunCallback();

    /// @brief Pointer to the keyboard controller.
    KeyboardControllerIf *m_KeyboardController;
    /// @brief Instance of this object (ModuleController class).
    static ModuleController *m_pInstance;
};

#endif