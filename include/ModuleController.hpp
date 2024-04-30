#ifndef MODULE_CONTROLLER_HPP
#define MODULE_CONTROLLER_HPP

#include <Arduino.h>
#include <Thread.h>

#include "ModuleConfig.hpp"

class KeyboardControllerIf;
class ViewIf;
class MenuViewIf;

class ModuleController : public Thread
{
public:
    static ModuleController *getInstance();

    ModuleController();

    void setKeyboardController(KeyboardControllerIf* keyboardController);

    void setViews(ViewIf* timeView, ViewIf* menuView, MenuViewIf* extendedMenuView);

private:

    enum ControllerState
    {
        STATE_DISPLAYING_TIME,
        STATE_DISPLAYING_MENU_SET_TIME,
        STATE_DISPLAYING_MENU_SET_DATE
    };

    void update();
    static void onRunCallback();

    /// @brief Current state of the machine state.
    ControllerState m_State;
    /// @brief Pointer to the keyboard controller.
    KeyboardControllerIf* m_KeyboardController;
    /// @brief Pointer to the time display view.
    ViewIf* m_TimeView;
    /// @brief Pointers to the Manu view, twwo as we have
    /// two different interfaces (see Interface Soup antipattern)
    /// Adaptive Code: Agile coding with design patterns and SOLID principles by Gary Mclean Hall.
    ViewIf* m_MenuView;
    MenuViewIf* m_ExtendedMenuView;


    static ModuleController *m_pInstance;
};

#endif