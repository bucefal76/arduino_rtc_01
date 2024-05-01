#include <Arduino.h>

#include "KeyboardController.hpp"
#include "ModuleConfig.hpp"

KeyboardController *KeyboardController::m_Instance = nullptr;

KeyboardController *KeyboardController::getInstance()
{
    if (nullptr == m_Instance)
    {
        m_Instance = new KeyboardController();
    }
    return m_Instance;
}

KeyboardController::KeyboardController()
    : m_isButtonBackPressDown(false), m_isButtonUpPressDown(false), m_isButtonDownPressDown(false), m_isButtonNextPressDown(false), m_ButtonCode(BUTTON_CODE_NONE)
{
    pinMode(BUTTON_BACK_IO_LINE, INPUT);
    pinMode(BUTTON_UP_IO_LINE, INPUT);
    pinMode(BUTTON_DOWN_IO_LINE, INPUT);
    pinMode(BUTTON_NEXT_IO_LINE, INPUT);

    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

void KeyboardController::onRunCallback()
{
    getInstance()->update();
}

void KeyboardController::update()
{

    if (digitalRead(BUTTON_BACK_IO_LINE) == HIGH)
    {
        if (true == m_isButtonBackPressDown)
        {
            m_isButtonBackPressDown = false;
        }
    }

    if (digitalRead(BUTTON_UP_IO_LINE) == HIGH)
    {
        if (true == m_isButtonUpPressDown)
        {
            m_isButtonUpPressDown = false;
        }
    }

    if (digitalRead(BUTTON_DOWN_IO_LINE) == HIGH)
    {
        if (true == m_isButtonDownPressDown)
        {
            m_isButtonDownPressDown = false;
        }
    }

    if (digitalRead(BUTTON_NEXT_IO_LINE) == HIGH)
    {
        if (true == m_isButtonNextPressDown)
        {
            m_isButtonNextPressDown = false;
        }
    }

    if (digitalRead(BUTTON_BACK_IO_LINE) == LOW)
    {
        if (false == m_isButtonBackPressDown)
        {
            m_isButtonBackPressDown = true;
            m_ButtonCode = ButtonCode::BUTTON_CODE_BACK;
            Serial.println(F("Back is down"));
        }
    }
    else if (digitalRead(BUTTON_UP_IO_LINE) == LOW)
    {
        if (false == m_isButtonUpPressDown)
        {
            m_isButtonUpPressDown = true;
            m_ButtonCode = ButtonCode::BUTTON_CODE_UP;
            Serial.println(F("Up is down"));
        }
    }

    else if (digitalRead(BUTTON_DOWN_IO_LINE) == LOW)
    {
        if (false == m_isButtonDownPressDown)
        {
            m_isButtonDownPressDown = true;
            m_ButtonCode = ButtonCode::BUTTON_CODE_DOWN;
            Serial.println(F("Down is down"));
        }
    }

    else if (digitalRead(BUTTON_NEXT_IO_LINE) == LOW)
    {
        if (false == m_isButtonNextPressDown)
        {
            m_isButtonNextPressDown = true;
            m_ButtonCode = ButtonCode::BUTTON_CODE_NEXT;
            Serial.println(F("Next is down"));
        }
    }
}

bool KeyboardController::isButtonPressDown() const
{
    if (m_isButtonBackPressDown || m_isButtonUpPressDown || m_isButtonDownPressDown || m_isButtonNextPressDown)
    {
        return true;
    }
    else
    {
        return false;
    }
}

KeyboardControllerIf::ButtonCode KeyboardController::getButtonCode()
{
    KeyboardControllerIf::ButtonCode code = m_ButtonCode;
    m_ButtonCode = KeyboardControllerIf::ButtonCode::BUTTON_CODE_NONE;
    return code;
}