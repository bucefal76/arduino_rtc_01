#ifndef DATE_SETUP_VIEW_HPP
#define DATE_SETUP_VIEW_HPP

#include "ViewDateSetupIf.hpp"
#include "Views/ViewBase.hpp"
#include <Thread.h>

/*
    The class implements the ViewIf and ViewDateSetupIf interfaces.
    Used to set new date settings.
    Displays year, month, day and extra icons to help navigate within the time setup mode.
*/

class ViewDateSetup : public ViewBase, public ViewDateSetupIf, public Thread
{
public:
    static ViewDateSetup *getInstance();

    ViewDateSetup();

    /// see ViewIf.
    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();
    /// see ViewDateSetupIf.
    virtual void setState(const ViewDateSetupState state);
    virtual ViewDateSetupState getState() const;
    virtual void putYear(const uint16_t year);
    virtual void putMonth(const uint8_t month);
    virtual void putDay(const uint8_t day);

private:
    void update();
    static void onRunCallback();

    ViewDateSetupIf::ViewDateSetupState m_State;
    uint16_t m_Year;
    uint8_t m_Month;
    uint8_t m_Day;

    static ViewDateSetup *m_pInstance;
};

#endif