#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP


#include <Thread.h>
#include "MenuViewIf.hpp"
#include "ViewIf.hpp"

class MenuView: public MenuViewIf, public ViewIf, public Thread
{
public:

    static MenuView* getInstance();

    MenuView();

    /// @brief MenuViewIf implementation.
    /// @param title 
    virtual void setTitle(const char* title);
    virtual void setContent(const char* content);

    /// @brief  ViewIf interface implementation.
    /// @param pLiquidCrystal 
    virtual void setLcd(LiquidCrystal* pLiquidCrystal);
    virtual void enable();
    virtual void disable();

private:

    void update();
    static void onRunCallback();
    LiquidCrystal *m_pLcd;
    bool m_isInitialized;
    const char* m_Title;
    const char* m_Content;
    uint8_t m_TitlePos;
    uint8_t m_ContentPos;

    static MenuView* m_pInstance;

};

#endif