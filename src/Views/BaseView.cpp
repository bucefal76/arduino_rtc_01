#include "Views/BaseView.hpp"
#include <LiquidCrystal.h>

LiquidCrystal *BaseView::m_pLcd = nullptr;
RtcDS1302<ThreeWire> *BaseView::m_Rtc = nullptr;

uint8_t BaseView::m_SpecialChars[VIEWS_SPECIAL_CHARACTERS_COUNT][VIEWS_SPECIAL_CHARACTERS_SIZE] = {
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
     B01000},
    {B00100,
     B01110,
     B11111,
     B00000,
     B11111,
     B01110,
     B00100}};

void BaseView::setLcd(LiquidCrystal *pLiquidCrystal)
{
    if (nullptr == m_pLcd)
    {
        m_pLcd = pLiquidCrystal;

        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_BACK_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_BACK_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_NEXT_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX][0]);
    }
}

void BaseView::setRtc(RtcDS1302<ThreeWire> *pRtc)
{
    m_Rtc = pRtc;
}

void BaseView::enable()
{
}

void BaseView::disable()
{
}