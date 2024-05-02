#ifndef TIME_SETUP_VIEW_HPP
#define TIME_SETUP_VIEW_HPP

#include "TimeSetupViewIf.hpp"
#include "Views/BaseView.hpp"
#include <Thread.h>

class LiquidCrystal;

class TimeSetupView : public BaseView, public TimeSetupViewIf, public Thread
{
public:
    static TimeSetupView *getInstance();

    TimeSetupView();

    virtual void setLcd(LiquidCrystal *pLcd);
    virtual void enable();
    virtual void disable();

    void putHours(const uint8_t hour);
    void putMinutes(const uint8_t hour);

private:
    void update();
    static void onRunCallback();
    uint8_t m_Hours;
    uint8_t m_Minutes;

    static TimeSetupView *m_pInstance;
};

#endif
