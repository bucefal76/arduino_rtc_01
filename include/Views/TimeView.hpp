#ifndef TIME_VIEW_HPP
#define TIME_VIEW_HPP

#include <Thread.h>

#include "Views/BaseView.hpp"

class TimeView : public Thread, public BaseView
{
public:
    static TimeView *getInstance();

    TimeView();

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static TimeView *m_Instance;
};

#endif