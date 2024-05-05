#ifndef STATE_DNEW_TIME_CONFIRMATION_HPP
#define STATE_DNEW_TIME_CONFIRMATION_HPP

#include "States/StateNewTimeSetup.hpp"

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