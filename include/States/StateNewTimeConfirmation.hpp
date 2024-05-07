#ifndef STATE_DNEW_TIME_CONFIRMATION_HPP
#define STATE_DNEW_TIME_CONFIRMATION_HPP

#include "States/StateNewTimeSetup.hpp"

/*
    This state controls the device's behavior when it asks the operator to accept
    the newly entered time. A confirmation dialog - are you sure?
*/

class StateNewTimeConfirmation : public StateNewTimeSetup
{
public:
    static StateBase *getInstance();

    StateNewTimeConfirmation();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

private:
    void setNewTime();

    virtual void enter();
    virtual void exit();

    static StateNewTimeConfirmation m_Instance;
};

#endif