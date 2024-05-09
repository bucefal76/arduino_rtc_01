#ifndef TIME_VIEW_HPP
#define TIME_VIEW_HPP

#include <Thread.h>

#include "Views/BaseView.hpp"

/*
    The class implements the ViewIf interface. It specializes in displaying a time and date.
*/

class TimeView : public Thread, public BaseView
{
public:
    static TimeView *getInstance();

    TimeView();

    virtual uint8_t getViewid() const;
    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static TimeView *m_Instance;
};

#endif