#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include "ViewIf.hpp"
#include "ModuleModelStateIf.hpp"

#define VIEWS_SPECIAL_CHARACTERS_COUNT 7U
#define VIEWS_SPECIAL_CHARACTERS_SIZE 8U
#define VIEWS_SPECIAL_CHARACTER_BACK_INDEX 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_INDEX 1U
#define VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX 2U
#define VIEWS_SPECIAL_CHARACTER_ALARM_ENABLED_INDEX 3U
#define VIEWS_SPECIAL_CHARACTER_ALARM_DISABLED_INDEX 4U
#define VIEWS_SPECIAL_CHARACTER_ALARM_ON_INDEX 5U
#define VIEWS_SPECIAL_CHARACTER_ALARM_OFF_INDEX 6U

#define VIEWS_SPECIAL_CHARACTER_BACK_COL_POSITION 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_COL_POSITION 15U

#if !defined(countof)
#define countof(a) (sizeof(a) / sizeof(a[0]))
#endif

class LiquidCrystal;

/*
    Among all classes that implement the ViewIf interface,
    there are some common functionality and data (for example, the pointer to the LCD driver).
    This class provides such common functionality for all ViewBase-derived classes.
*/

class ViewBase : public ViewIf
{
public:
    /// @brief  Set pointer to the LCD driver.
    /// @param pLiquidCrystal
    virtual void setLcd(LiquidCrystal *pLiquidCrystal);
    /// @brief Set pointer to the Model. Model represents the RTC.
    /// @param pModel
    virtual void setModel(ModuleModelStateIf *pModel);
    // See ViewIf.
    virtual void enable();
    virtual void disable();

protected:
    static uint8_t m_SpecialChars[VIEWS_SPECIAL_CHARACTERS_COUNT][VIEWS_SPECIAL_CHARACTERS_SIZE];
    static LiquidCrystal *m_pLcd;
    static ModuleModelStateIf *m_pModel;
};

#endif