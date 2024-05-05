#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

/*
    This interface declares the functionality needed to use a simple keyboard.
*/

class KeyboardControllerIf
{

public:
    /// @brief Code of pressed button
    enum ButtonCode
    {
        BUTTON_CODE_NONE = 0,
        BUTTON_CODE_BACK,
        BUTTON_CODE_UP,
        BUTTON_CODE_DOWN,
        BUTTON_CODE_NEXT
    };

    /// @brief Returns true if button is press down (any button).
    /// @return True in any button is pressed now.
    virtual bool isButtonPressDown() const = 0;
    /// @brief Returns press button code.
    /// @return Code of the pressed button.
    virtual ButtonCode getButtonCode() = 0;
};

#endif