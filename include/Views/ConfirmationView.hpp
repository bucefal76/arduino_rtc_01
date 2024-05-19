#ifndef CONFIRMATION_VIEW_HPP
#define CONFIRMATION_VIEW_HPP

#include <Thread.h>
#include "Views/ViewBase.hpp"

/*
    The class implements the ViewIf interface.
    Displays a confirmation question (Approve?) with two possible choices (Yes?/No?).
*/

class ConfirmationView : public Thread, public ViewBase
{
public:
    static ConfirmationView *getInstance();

    ConfirmationView();

    virtual uint8_t getViewid() const;
    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static ConfirmationView *m_Instance;
};

#endif