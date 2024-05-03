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

class ModuleController : public Thread
{
public:
    static ModuleController *getInstance();

    ModuleController();

    void setKeyboardController(KeyboardControllerIf *keyboardController);

    void setViews(ViewIf *timeView,
                  ViewIf *menuView,
                  MenuViewIf *extendedMenuView,
                  ViewIf *timeSetupView,
                  TimeSetupViewIf *extendedTimeSetupView);

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