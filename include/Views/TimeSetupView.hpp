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

    virtual void enable();
    virtual void disable();

    virtual void setState(TimeSetupViewState state);
    virtual TimeSetupViewState getState() const;
    void putHours(const uint8_t hours);
    void putMinutes(const uint8_t minutes);

private:
    void update();
    static void onRunCallback();
    uint8_t m_Hours;
    uint8_t m_Minutes;
    TimeSetupViewIf::TimeSetupViewState m_State;

    static TimeSetupView *m_pInstance;
};

#endif
