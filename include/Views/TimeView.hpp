#ifndef TIME_VIEW_HPP
#define TIME_VIEW_HPP

#include <Thread.h>
#include <RtcDS1302.h>

#include "Views/BaseView.hpp"

class LiquidCrystal;

class TimeView : public Thread, public BaseView
{
public:
    static TimeView *getInstance();

    TimeView();

    void setRtc(RtcDS1302<ThreeWire> *pRtc);

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    RtcDS1302<ThreeWire> *m_Rtc;

    static TimeView *m_Instance;
};

#endif