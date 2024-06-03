#include "Controller/ModuleController.hpp"
#include "Controller/States/StateBase.hpp"
#include "Controller/States/StateDisplayingTime.hpp"
#include "KeyboardControllerIf.hpp"
#include "ViewMenuIf.hpp"
#include "ViewIf.hpp"

ModuleController *ModuleController::m_pInstance = nullptr;

ModuleController *ModuleController::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ModuleController();
    }
    return m_pInstance;
}

ModuleController::ModuleController()
    : m_KeyboardController(nullptr)
{
    // Initialize the state machine with first state
    StateBase::setCurrentState(StateDisplayingTime::getInstance());

    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

void ModuleController::setKeyboardController(KeyboardControllerIf *keyboardController)
{
    m_KeyboardController = keyboardController;
}

void ModuleController::addView(ViewIf *pView)
{
    StateBase::addView(pView);
}

void ModuleController::addExtendedView(const uint8_t viewId, ViewExtendedIf *pExtendedView)
{
    StateBase::addExtendedView(viewId, pExtendedView);
}

void ModuleController::setModel(ModuleModelIf *pModel)
{
    StateBase::setModel(pModel);
}

void ModuleController::setModelState(ModuleModelStateIf *pModelState)
{
    StateBase::setModelState(pModelState);
}

void ModuleController::update()
{
    /*
        This is the primary control loop for the clock application.
        It checks if any key is pressed on the keyboard and sends the corresponding
        event to the currently selected state of the State Machine.
        The current state of the State Machine then executes the required actions.
    */

    if (m_KeyboardController->isButtonPressDown())
    {
        const KeyboardControllerIf::ButtonCode button = m_KeyboardController->getButtonCode();

        if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NONE != button)
        {
            StateBase::getCurrentState()->processButton(button);
        }
    }

    /*
        Then also current state of the State machine is kick to update its own logic, if needed.
    */

    StateBase::getCurrentState()->update();
}

void ModuleController::onRunCallback()
{
    getInstance()->update();
}
