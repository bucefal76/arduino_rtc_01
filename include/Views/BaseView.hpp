#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include "ViewIf.hpp"
#include <RtcDS1302.h>

class LiquidCrystal;

class BaseView : public ViewIf
{
public:
    /// @brief  Set pointer to the LCD driver.
    /// @param pLiquidCrystal
    virtual void setLcd(LiquidCrystal *pLiquidCrystal);
    /// @brief  Set popinter to the Clock.
    /// @param pRtc
    virtual void setRtc(RtcDS1302<ThreeWire> *pRtc);

    virtual void enable();
    virtual void disable();

protected:
    static LiquidCrystal *m_pLcd;
    static RtcDS1302<ThreeWire> *m_Rtc;
};

#endif