#ifndef THREAD_KEYBOARD_HPP
#define THREAD_KEYBOARD_HPP

#include <Thread.h>

#include "KeyboardControllerIf.hpp"

/*
    The class implements KeyboardControllerIf.
    In this case, all 4 supported buttons are connected to the pull-up resistors.
    When press down the IO line is taken to the ground (0V).
    The buttons are used in this formula: Back, Up, Down, Next.
    Check MoppduleConfig.hpp for the line/pin # used with this keyboard.
*/

class KeyboardController : public Thread, public KeyboardControllerIf
{

public:
    static KeyboardController *getInstance();

    KeyboardController();

    virtual bool isButtonPressDown() const;

    virtual KeyboardControllerIf::ButtonCode getButtonCode();

private:
    void update();
    static void onRunCallback();

    bool m_isButtonBackPressDown;
    bool m_isButtonUpPressDown;
    bool m_isButtonDownPressDown;
    bool m_isButtonNextPressDown;

    ButtonCode m_ButtonCode;

    static KeyboardController *m_Instance;
};

#endif