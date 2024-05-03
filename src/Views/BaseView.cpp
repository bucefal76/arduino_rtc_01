#include "Views/BaseView.hpp"
#include <LiquidCrystal.h>

LiquidCrystal *BaseView::m_pLcd = nullptr;
RtcDS1302<ThreeWire> *BaseView::m_Rtc = nullptr;

void BaseView::setLcd(LiquidCrystal *pLiquidCrystal)
{
    if (nullptr == m_pLcd)
    {
        m_pLcd = pLiquidCrystal;
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