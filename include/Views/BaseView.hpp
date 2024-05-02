#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include "ViewIf.hpp"

class LiquidCrystal;

class BaseView : public ViewIf
{
public:
    /// @brief  ViewIf interface implementation.
    /// @param pLiquidCrystal
    virtual void setLcd(LiquidCrystal *pLiquidCrystal);
    virtual void enable();
    virtual void disable();

protected:
    static LiquidCrystal *m_pLcd;
};

#endif