#ifndef TIME_SETUP_VIEW_HPP
#define TIME_SETUP_VIEW_HPP

#include "ViewTimeSetupIf.hpp"
#include "Views/ViewBase.hpp"
#include <Thread.h>

/*
    The class implements the ViewIf and ViewTimeSetupIf interfaces.
    Used to set new time settings.
    Displays hours, minutes, and extra icons to help navigate within the time setup mode.
*/

class ViewTimeSetup : public ViewBase, public ViewTimeSetupIf, public Thread
{
public:
    static ViewTimeSetup *getInstance();

    ViewTimeSetup();

    /// see ViewIf.
    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();
    /// see ViewTimeSetupIf.
    virtual void setState(ViewTimeSetupState state);
    virtual ViewTimeSetupState getState() const;
    void putHours(const uint8_t hours);
    void putMinutes(const uint8_t minutes);

private:
    void update();
    static void onRunCallback();
    uint8_t m_Hours;
    uint8_t m_Minutes;
    ViewTimeSetupIf::ViewTimeSetupState m_State;

    static ViewTimeSetup *m_pInstance;
};

#endif
