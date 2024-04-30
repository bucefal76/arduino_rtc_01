#include "ModuleController.hpp"
#include "KeyboardControllerIf.hpp"
#include "MenuViewIf.hpp"
#include "TimeView.hpp"

static const char *CAPTION_MENU = "MENU\0";
static const char *CAPTION_SET_TIME = "SET TIME\0";
static const char *CAPTION_SET_DATE = "SET DATE\0";

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
    : m_State(STATE_DISPLAYING_TIME), m_KeyboardController(nullptr), m_TimeView(nullptr), m_MenuView(nullptr), m_ExtendedMenuView(nullptr)
{
    setInterval(STATE_MACHINE_UPDATE_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

void ModuleController::setKeyboardController(KeyboardControllerIf *keyboardController)
{
    m_KeyboardController = keyboardController;
}

void ModuleController::setViews(ViewIf *timeView, ViewIf *menuView, MenuViewIf *extendedMenuView)
{
    m_TimeView = timeView;
    m_MenuView = menuView;
    m_ExtendedMenuView = extendedMenuView;
}

void ModuleController::update()
{
    if (nullptr != m_KeyboardController)
    {
        if (m_KeyboardController->isButtonPressDown())
        {
            const KeyboardControllerIf::ButtonCode button = m_KeyboardController->getButtonCode();

            switch (m_State)
            {
                case STATE_DISPLAYING_TIME:
                {
                    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
                    {
                        m_TimeView->disable();
                        m_MenuView->enable();
                        m_ExtendedMenuView->setTitle(CAPTION_MENU);
                        m_ExtendedMenuView->setContent(CAPTION_SET_DATE);

                        m_State = STATE_DISPLAYING_MENU_SET_DATE;
                    }
                    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
                    {
                        m_TimeView->disable();
                        m_MenuView->enable();
                        m_ExtendedMenuView->setTitle(CAPTION_MENU);
                        m_ExtendedMenuView->setContent(CAPTION_SET_TIME);

                        m_State = STATE_DISPLAYING_MENU_SET_TIME;
                    }

                    break;
                }

                case STATE_DISPLAYING_MENU_SET_TIME:
                {
                    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
                    {
                        m_ExtendedMenuView->setTitle(CAPTION_MENU);
                        m_ExtendedMenuView->setContent(CAPTION_SET_DATE);

                        m_State = STATE_DISPLAYING_MENU_SET_DATE;
                    }
                    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
                    {
                        m_MenuView->disable();
                        m_TimeView->enable();

                        m_State = STATE_DISPLAYING_TIME;
                    }

                    break;
                }

                case STATE_DISPLAYING_MENU_SET_DATE:
                {
                    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
                    {
                        m_MenuView->disable();
                        m_TimeView->enable();
                        
                        m_State = STATE_DISPLAYING_TIME;                        
                    }
                    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
                    {
                        m_ExtendedMenuView->setTitle(CAPTION_MENU);
                        m_ExtendedMenuView->setContent(CAPTION_SET_TIME);

                        m_State = STATE_DISPLAYING_MENU_SET_TIME;
                    }

                    break;                    
                }
            
            }
        }
    }
}

void ModuleController::onRunCallback()
{
    getInstance()->update();
}