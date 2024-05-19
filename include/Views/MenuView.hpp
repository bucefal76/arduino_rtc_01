#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <Thread.h>
#include "MenuViewIf.hpp"
#include "Views/ViewBase.hpp"

/*
    The class implements MenuViewIf. Displays settings menu with navigation icons.
*/

class MenuView : public MenuViewIf, public ViewBase, public Thread
{
public:
    static MenuView *getInstance();

    MenuView();

    /// @brief MenuViewIf implementation.
    /// @param title
    virtual void setTitle(const char *title);
    virtual void setContent(const char *content);
    /// @brief ViewIf implementation.
    virtual uint8_t getViewid() const;
    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();
    const char *m_Title;
    const char *m_Content;
    uint8_t m_TitlePos;
    uint8_t m_ContentPos;

    static MenuView *m_pInstance;
};

#endif