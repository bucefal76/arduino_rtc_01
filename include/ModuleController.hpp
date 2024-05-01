#ifndef MODULE_CONTROLLER_HPP
#define MODULE_CONTROLLER_HPP

#include <Arduino.h>
#include <Thread.h>

#include "ModuleConfig.hpp"

class StateBase;
class KeyboardControllerIf;
class ViewIf;
class MenuViewIf;

class ModuleController : public Thread
{
public:
    static ModuleController *getInstance();

    ModuleController();

    void setKeyboardController(KeyboardControllerIf *keyboardController);

    void setViews(ViewIf *timeView, ViewIf *menuView, MenuViewIf *extendedMenuView);

private:
    void update();

    static void onRunCallback();

    /// @brief Pointer to the keyboard controller.
    KeyboardControllerIf *m_KeyboardController;
    /// @brief Instance of this object (ModuleController class).
    static ModuleController *m_pInstance;
};

#endif