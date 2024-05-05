#include "ModuleController.hpp"
#include "KeyboardControllerIf.hpp"
#include "MenuViewIf.hpp"
#include "ViewIf.hpp"
#include "States/StateBase.hpp"
#include "States/StateDisplayingTime.hpp"

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
    // Initalize the state machine with first state
    StateBase::setCurrentState(StateDisplayingTime::getInstance());

    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

void ModuleController::setKeyboardController(KeyboardControllerIf *keyboardController)
{
    m_KeyboardController = keyboardController;
}

void ModuleController::setViews(ViewIf *timeView,
                                ViewIf *menuView,
                                MenuViewIf *extendedMenuView,
                                ViewIf *timeSetupView,
                                TimeSetupViewIf *extendedTimeSetupView,
                                ViewIf *confirmationView)
{
    /// Initalize state machine with views to play with:
    StateBase::setViews(timeView, menuView, extendedMenuView, timeSetupView, extendedTimeSetupView, confirmationView);
}

void ModuleController::setRtc(RtcDS1302<ThreeWire> *rtc)
{
    StateBase::setRtc(rtc);
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
}

void ModuleController::onRunCallback()
{
    getInstance()->update();
}
