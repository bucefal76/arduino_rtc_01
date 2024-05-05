#ifndef CONFIRMATION_VIEW_HPP
#define CONFIRMATION_VIEW_HPP

#include <Thread.h>
#include "Views/BaseView.hpp"

/*
    The class implements the ViewIf interface.
    Displays questions (Approve?) with two possible choices (Yes?/No?).
*/

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