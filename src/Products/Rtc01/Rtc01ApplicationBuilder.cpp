#include "Products/Rtc01/Rtc01ApplicationBuilder.hpp"
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"

#include "KeyboardController.hpp"
#include "ModuleController.hpp"
#include "Views/MenuView.hpp"
#include "Views/TimeView.hpp"
#include "Views/TimeSetupView.hpp"
#include "Views/ConfirmationView.hpp"
#include "Views/DateSetupView.hpp"

Rtc01ApplicationBuilder::Rtc01ApplicationBuilder()
{
}

void Rtc01ApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    ModuleApplicationBuilder::initalizeRct();

    setupThreads(rApplication);
}

void Rtc01ApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
    /*
        Here functionality of the selected clock product is built:
    */

    LiquidCrystal *lcd = new LiquidCrystal(RS_IO_LINE, EN_IO_LINE, D4_IO_LINE, D5_IO_LINE, D6_IO_LINE, D7_IO_LINE);
    if (nullptr != lcd)
    {
        lcd->begin(LCD_MAX_COLS, LCD_MAX_ROWS);
    }

    // Now is a time to create and connect basic functional blocks of the source codes. First, views:
    if (nullptr != TimeView::getInstance())
    {
        TimeView::getInstance()->setLcd(lcd);
        TimeView::getInstance()->setRtc(&m_rtc);
    }

    rApplication.addThread(TimeView::getInstance());
    rApplication.addThread(MenuView::getInstance());
    rApplication.addThread(TimeSetupView::getInstance());
    rApplication.addThread(ConfirmationView::getInstance());
    rApplication.addThread(DateSetupView::getInstance());

    // Then the keyboard controller...
    rApplication.addThread(KeyboardController::getInstance());

    // And then the application controller.
    rApplication.addThread(ModuleController::getInstance());
    // Now created modules are injected to the application controller (dependency injection).

    if (nullptr != ModuleController::getInstance())
    {
        ModuleController::getInstance()->setKeyboardController(KeyboardController::getInstance());
        ModuleController::getInstance()->setViews(TimeView::getInstance(),
                                                  MenuView::getInstance(),
                                                  MenuView::getInstance(),
                                                  TimeSetupView::getInstance(),
                                                  TimeSetupView::getInstance(),
                                                  ConfirmationView::getInstance(),
                                                  DateSetupView::getInstance(),
                                                  DateSetupView::getInstance());
        ModuleController::getInstance()->setRtc(&m_rtc);
    }
}
