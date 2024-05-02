#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <Thread.h>
#include "MenuViewIf.hpp"
#include "Views/BaseView.hpp"

class MenuView : public MenuViewIf, public BaseView, public Thread
{
public:
    static MenuView *getInstance();

    MenuView();

    /// @brief MenuViewIf implementation.
    /// @param title
    virtual void setTitle(const char *title);
    virtual void setContent(const char *content);

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();
    bool m_isInitialized;
    const char *m_Title;
    const char *m_Content;
    uint8_t m_TitlePos;
    uint8_t m_ContentPos;

    static MenuView *m_pInstance;
};

#endif