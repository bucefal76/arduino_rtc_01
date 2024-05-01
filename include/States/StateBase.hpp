#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "KeyboardControllerIf.hpp"

static const char *CAPTION_MENU = "MENU\0";

class ViewIf;
class MenuViewIf;

class StateBase
{
public:
    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

    static void setViews(ViewIf *timeView, ViewIf *menuView, MenuViewIf *extendedMenuView);

    static StateBase *getCurrentState();
    static void setCurrentState(StateBase *state);

protected:
    void trasitToNextState(StateBase *pNexState);

    virtual void enter() = 0;

    virtual void exit() = 0;

    /// @brief
    static StateBase *m_pCurrentState;

    /// @brief Pointer to the time display view.
    static ViewIf *m_TimeView;
    /// @brief Pointers to the Manu view, twwo as we have
    /// two different interfaces (see Interface Soup antipattern)
    /// Adaptive Code: Agile coding with design patterns and SOLID principles by Gary Mclean Hall.
    static ViewIf *m_MenuView;
    static MenuViewIf *m_ExtendedMenuView;
};

#endif