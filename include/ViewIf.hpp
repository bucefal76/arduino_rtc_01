#ifndef VIEW_IF_HPP
#define VIEW_IF_HPP

class LiquidCrystal;

class ViewIf
{
public:

    virtual void setLcd(LiquidCrystal* pLcd) = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;

};


#endif