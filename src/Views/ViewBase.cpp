#include "Views/ViewBase.hpp"
#include <LiquidCrystal.h>

LiquidCrystal *ViewBase::m_pLcd = nullptr;
ModuleModelStateIf *ViewBase::m_pModel = nullptr;

uint8_t ViewBase::m_SpecialChars[VIEWS_SPECIAL_CHARACTERS_COUNT][VIEWS_SPECIAL_CHARACTERS_SIZE] = {
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
     B00100},
    {B01110,
     B01010,
     B01010,
     B01010,
     B01010,
     B01010,
     B11011},
    {B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B11111},
    {B00111,
     B00100,
     B00100,
     B00100,
     B00100,
     B00100,
     B11100},
    {B11100,
     B00100,
     B00100,
     B00100,
     B00100,
     B00100,
     B00111}};

void ViewBase::setLcd(LiquidCrystal *pLiquidCrystal)
{
    if (nullptr == m_pLcd)
    {
        m_pLcd = pLiquidCrystal;

        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_BACK_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_BACK_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_NEXT_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_NEXT_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_ALARM_ENABLED_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_ALARM_ENABLED_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_ALARM_DISABLED_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_ALARM_DISABLED_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_ALARM_ON_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_ALARM_ON_INDEX][0]);
        m_pLcd->createChar(VIEWS_SPECIAL_CHARACTER_ALARM_OFF_INDEX, &m_SpecialChars[VIEWS_SPECIAL_CHARACTER_ALARM_OFF_INDEX][0]);
    }
}

void ViewBase::setModel(ModuleModelStateIf *pModel)
{
    if (nullptr == m_pModel)
    {
        m_pModel = pModel;
    }
}

void ViewBase::enable()
{
}

void ViewBase::disable()
{
}