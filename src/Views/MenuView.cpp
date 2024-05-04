#include <LiquidCrystal.h>

#include "Views/MenuView.hpp"
#include "ModuleConfig.hpp"

#define MENU_TITLE_ROW 0U
#define MENU_CONTENT_ROW 1U

MenuView *MenuView::m_pInstance = nullptr;

MenuView *MenuView::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new MenuView();
    }
    return m_pInstance;
}

MenuView::MenuView()
    : m_Title(nullptr), m_Content(nullptr), m_TitlePos(0U), m_ContentPos(0U)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void MenuView::setTitle(const char *title)
{
    m_Title = title;
    const int length = strlen(m_Title);
    m_TitlePos = LCD_MAX_COLS - length;
    m_TitlePos = m_TitlePos / 2;
}

void MenuView::setContent(const char *content)
{
    m_Content = content;
    const int length = strlen(m_Content);
    m_ContentPos = LCD_MAX_COLS - length;
    m_ContentPos = m_ContentPos / 2;
}

void MenuView::enable()
{
    if (nullptr != m_pLcd)
    {
        enabled = true;
        m_pLcd->clear();
    }
}

void MenuView::disable()
{
    enabled = false;
}

void MenuView::update()
{
    if (nullptr != m_pLcd)
    {
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, 1U);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_BACK_INDEX));
        m_pLcd->setCursor(VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION, 1U);
        m_pLcd->write(byte(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX));

        m_pLcd->setCursor(m_TitlePos, MENU_TITLE_ROW);
        m_pLcd->write(m_Title);

        m_pLcd->setCursor(m_ContentPos, MENU_CONTENT_ROW);
        m_pLcd->write(m_Content);
    }
}

void MenuView::onRunCallback()
{
    getInstance()->update();
}