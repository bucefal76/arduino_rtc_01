#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

class KeyboardControllerIf
{

public:

    enum ButtonCode
    {
        BUTTON_CODE_NONE = 0,
        BUTTON_CODE_BACK,
        BUTTON_CODE_UP,
        BUTTON_CODE_DOWN,
        BUTTON_CODE_NEXT
    };

    virtual bool isButtonPressDown() const = 0;

    virtual ButtonCode getButtonCode() = 0;

};

#endif