#ifndef CONFIRMATION_VIEW_HPP
#define CONFIRMATION_VIEW_HPP

#include <Thread.h>
#include "Views/BaseView.hpp"

class ConfirmationView : public Thread, public BaseView
{
public:
    static ConfirmationView *getInstance();

    ConfirmationView();

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static ConfirmationView *m_Instance;
};

#endif