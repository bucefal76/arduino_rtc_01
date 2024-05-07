#ifndef DATE_SETUP_VIEW_HPP
#define DATE_SETUP_VIEW_HPP

#include "DateSetupViewIf.hpp"
#include "Views/BaseView.hpp"
#include <Thread.h>

/*
    The class implements the ViewIf and DateSetupViewIf interfaces.
    Used to set new date settings.
    Displays year, month, day and extra icons to help navigate within the time setup mode.
*/

class DateSetupView : public BaseView, public DateSetupViewIf, public Thread
{
public:
    static DateSetupView *getInstance();

    DateSetupView();

    /// see ViewIf.
    virtual void enable();
    virtual void disable();
    /// see DateSetupViewIf.
    virtual void setState(const DateSetupViewState state);
    virtual DateSetupViewState getState() const;
    virtual void putYear(const uint16_t year);
    virtual void putMonth(const uint8_t month);
    virtual void putDay(const uint8_t day);

private:
    void update();
    static void onRunCallback();

    DateSetupViewIf::DateSetupViewState m_State;
    uint16_t m_Year;
    uint8_t m_Month;
    uint8_t m_Day;

    static DateSetupView *m_pInstance;
};

#endif