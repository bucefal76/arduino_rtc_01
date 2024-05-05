#ifndef TIME_SETUP_VIEW_HPP
#define TIME_SETUP_VIEW_HPP

#include "TimeSetupViewIf.hpp"
#include "Views/BaseView.hpp"
#include <Thread.h>

/*
    The class implements the ViewIf and TimeSetupViewIf interfaces.
    Used to set new time settings.
    Displays hours, minutes, and extra icons to help navigate within the time setup mode.
*/

class TimeSetupView : public BaseView, public TimeSetupViewIf, public Thread
{
public:
    static TimeSetupView *getInstance();

    TimeSetupView();

    /// see ViewIf.
    virtual void enable();
    virtual void disable();
    /// see TimeSetupViewIf.
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
