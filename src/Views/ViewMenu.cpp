#include <LiquidCrystal.h>

#include "Views/ViewMenu.hpp"
#include "ModuleConfig.hpp"

#define MENU_TITLE_ROW 0U
#define MENU_CONTENT_ROW 1U

ViewMenu *ViewMenu::m_pInstance = nullptr;

ViewMenu *ViewMenu::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ViewMenu();
    }
    return m_pInstance;
}

ViewMenu::ViewMenu()
    : m_Title(nullptr), m_Content(nullptr), m_TitlePos(0U), m_ContentPos(0U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void ViewMenu::setTitle(const char *title)
{
    m_Title = title;
    const int length = strlen(m_Title);
    m_TitlePos = LCD_MAX_COLS - length;
    m_TitlePos = m_TitlePos / 2;
}

void ViewMenu::setContent(const char *content)
{
    m_Content = content;
    const int length = strlen(m_Content);
    m_ContentPos = LCD_MAX_COLS - length;
    m_ContentPos = m_ContentPos / 2;
}

uint8_t ViewMenu::getViewId() const
{
    return VIEW_ID_MENU_VIEW;
}

void ViewMenu::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void ViewMenu::disable()
{
    enabled = false;
}

void ViewMenu::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COL_POSITION, 1U);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COL_POSITION, 1U);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

        m_pLcd->setCursor(m_TitlePos, MENU_TITLE_ROW);
        m_pLcd->write(m_Title);

        m_pLcd->setCursor(m_ContentPos, MENU_CONTENT_ROW);
        m_pLcd->write(m_Content);
    }
}

void ViewMenu::onRunCallback()
{
    getInstance()->update();
}