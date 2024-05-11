#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include "ViewIf.hpp"
#include "ModuleModelIf.hpp"

#define VIEWS_SPECIAL_CHARACTERS_COUNT 3U
#define VIEWS_SPECIAL_CHARACTERS_SIZE 8U
#define VIEWS_SPECIAL_CHARACTER_BACK_INDEX 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_INDEX 1U
#define VIEWS_SPECIAL_CHARACTER_MODIFICATION_INDEX 2U

#define VIEWS_SPECIAL_CHARACTER_BACK_COLUMN_POSITION 0U
#define VIEWS_SPECIAL_CHARACTER_NEXT_COLUMN_POSITION 15U

#if !defined(countof)
#define countof(a) (sizeof(a) / sizeof(a[0]))
#endif

class LiquidCrystal;

/*
    Among all classes that implement the ViewIf interface,
    there are some common functionality and data (for example, the pointer to the LCD driver).
    This class provides such common functionality for all BaseView-derived classes.
*/

class BaseView : public ViewIf
{
public:
    /// @brief  Set pointer to the LCD driver.
    /// @param pLiquidCrystal
    virtual void setLcd(LiquidCrystal *pLiquidCrystal);
    /// @brief Set poiter to the Model. Model represnts the RTC.
    /// @param pModel
    virtual void setModel(ModuleModelIf *pModel);
    // See ViewIf.
    virtual void enable();
    virtual void disable();

protected:
    static uint8_t m_SpecialChars[VIEWS_SPECIAL_CHARACTERS_COUNT][VIEWS_SPECIAL_CHARACTERS_SIZE];
    static LiquidCrystal *m_pLcd;
    static ModuleModelIf *m_pModel;
};

#endif