#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include "ViewIf.hpp"
#include <RtcDS1302.h>

#define VIEWS_SPECIAL_CHARACTERS_COUNT 3U
#define VIEWS_SPECIAL_CHARACTERS_SIZE 8U
#define VIEWS_SPECIAL_CHARACTER_BACK_INDEX 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_INDEX 1U
#define VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX 2U

#define VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION 15U

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
    static uint8_t m_SpecialChars[VIEWS_SPECIAL_CHARACTERS_COUNT][VIEWS_SPECIAL_CHARACTERS_SIZE];
    static LiquidCrystal *m_pLcd;
    static RtcDS1302<ThreeWire> *m_Rtc;
};

#endif