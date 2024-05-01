#include <LiquidCrystal.h>

#include "MenuView.hpp"
#include "ModuleConfig.hpp"

#define MENU_SPECIAL_CHARACTER_COUNT 2U
#define MENU_SPECIAL_CHARACTER_SIZE 8U

#define MENU_SPECIAL_CHARACTER_BACK 0U
#define MENU_SPECIAL_CHARACTER_NEXT 1U

#define MENU_SPECIAL_CHARACTER_BACK_COLUMN_POSITION 0U
#define MENU_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION 15U

#define MENU_TITLE_ROW 0U
#define MENU_CONTENT_ROW 1U

static uint8_t barChars[MENU_SPECIAL_CHARACTER_COUNT][MENU_SPECIAL_CHARACTER_SIZE] = {
    {B00010,
     B00110,
     B01110,
     B11110,
     B01110,
     B00110,
     B00010},
    {B01000,
     B01100,
     B01110,
     B01111,
     B01110,
     B01100,
     B01000}};

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
    : m_pLcd(nullptr), m_isInitialized(false), m_Title(nullptr), m_Content(nullptr), m_TitlePos(0U), m_ContentPos(0U)
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

void MenuView::setLcd(LiquidCrystal *pLcd)
{
    m_pLcd = pLcd;
}

void MenuView::enable()
{
    if (nullptr != m_pLcd)
    {
        if (!m_isInitialized)
        {
            m_pLcd->createChar(MENU_SPECIAL_CHARACTER_BACK, &barChars[MENU_SPECIAL_CHARACTER_BACK][0]);
            m_pLcd->createChar(MENU_SPECIAL_CHARACTER_NEXT, &barChars[MENU_SPECIAL_CHARACTER_NEXT][0]);
        }
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
        m_pLcd->setCursor(MENU_SPECIAL_CHARACTER_BACK_COLUMN_POSITION, 1U);
        m_pLcd->write(byte(MENU_SPECIAL_CHARACTER_BACK));
        m_pLcd->setCursor(MENU_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION, 1U);
        m_pLcd->write(byte(MENU_SPECIAL_CHARACTER_NEXT));

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