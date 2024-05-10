#ifndef SET_NEW_DATA_CONFIRMATION_HPP
#define SET_NEW_DATA_CONFIRMATION_HPP

#include "Controller/States/StateNewDateSetup.hpp"

/*
    This state controls the device's behavior when it asks the operator to accept
    the newly entered date. A confirmation dialog - are you sure?
*/

class StateNewDateConfirmation : public StateNewDateSetup
{
public:
    static StateBase *getInstance();

    StateNewDateConfirmation();

    virtual void processButton(const KeyboardControllerIf::ButtonCode button);

private:
    void setNewDate();

    virtual void enter();
    virtual void exit();

    static StateNewDateConfirmation m_Instance;
};

#endif
