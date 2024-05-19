#ifndef TIME_VIEW_HPP
#define TIME_VIEW_HPP

#include <Thread.h>

#include "Views/ViewBase.hpp"

/*
    The class implements the ViewIf interface. It specializes in displaying a time and date.
*/

class ViewTime : public Thread, public ViewBase
{
public:
    static ViewTime *getInstance();

    ViewTime();

    virtual uint8_t getViewId() const;
    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static ViewTime *m_Instance;
};

#endif