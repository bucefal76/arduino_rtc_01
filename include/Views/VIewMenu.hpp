#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <Thread.h>
#include "ViewMenuIf.hpp"
#include "Views/ViewBase.hpp"

/*
    The class implements ViewMenuIf. Displays settings menu with navigation icons.
*/

class ViewMenu : public ViewMenuIf, public ViewBase, public Thread
{
public:
    static ViewMenu *getInstance();

    ViewMenu();

    /// @brief ViewMenuIf implementation.
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

    static ViewMenu *m_pInstance;
};

#endif