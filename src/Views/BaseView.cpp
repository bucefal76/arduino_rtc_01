#include "Views/BaseView.hpp"
#include "LiquidCrystal.h"

LiquidCrystal *BaseView::m_pLcd = nullptr;

void BaseView::setLcd(LiquidCrystal *pLiquidCrystal)
{
    if (nullptr == m_pLcd)
    {
        m_pLcd = pLiquidCrystal;
    }
}

void BaseView::enable()
{
}

void BaseView::disable()
{
}