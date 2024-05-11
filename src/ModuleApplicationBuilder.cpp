#include <LiquidCrystal.h>

#include "ModuleApplicationBuilder.hpp"
#include "Controller/KeyboardController.hpp"
#include "Controller/ModuleController.hpp"
#include "ModuleModelIf.hpp"
#include "Model/ModuleModel.hpp"
#include "ModuleApplicationIf.hpp"
#include "Views/ConfirmationView.hpp"
#include "Views/DateSetupView.hpp"
#include "Views/MenuView.hpp"
#include "Views/TimeSetupView.hpp"
#include "Views/TimeView.hpp"

void ModuleApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    setupThreads(rApplication);
}

void ModuleApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
    /*
        Here functionality of the selected clock product is built:
    */

    ModuleModel *model = ModuleModel::getInstance();

    LiquidCrystal *lcd = new LiquidCrystal(RS_IO_LINE, EN_IO_LINE, D4_IO_LINE, D5_IO_LINE, D6_IO_LINE, D7_IO_LINE);
    if (nullptr != lcd)
    {
        lcd->begin(LCD_MAX_COLS, LCD_MAX_ROWS);
    }

    // Now is a time to create and connect basic functional blocks of the source codes. First, views:
    if (nullptr != TimeView::getInstance())
    {
        TimeView::getInstance()->setLcd(lcd);
        TimeView::getInstance()->setModel(model);
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

        ModuleController::getInstance()->setExtendedViews(MenuView::getInstance(),
                                                          TimeSetupView::getInstance(),
                                                          DateSetupView::getInstance());

        ModuleController::getInstance()->addView(TimeView::getInstance());
        ModuleController::getInstance()->addView(MenuView::getInstance());
        ModuleController::getInstance()->addView(TimeSetupView::getInstance());
        ModuleController::getInstance()->addView(ConfirmationView::getInstance());
        ModuleController::getInstance()->addView(DateSetupView::getInstance());

        ModuleController::getInstance()->setRtc(model->getRtc());
    }
}
