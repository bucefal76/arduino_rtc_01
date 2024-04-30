#ifndef THREAD_KEYBOARD_HPP
#define THREAD_KEYBOARD_HPP

#include <Thread.h>

#include "KeyboardControllerIf.hpp"

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