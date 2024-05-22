#include <LiquidCrystal.h>

#include "ModuleApplicationBuilder.hpp"
#include "Controller/KeyboardController.hpp"
#include "Controller/ModuleController.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"
#include "Model/ModuleModel.hpp"
#include "ModuleApplicationIf.hpp"
#include "Views/ViewConfirmationQuestion.hpp"
#include "Views/ViewDateSetup.hpp"
#include "Views/ViewMenu.hpp"
#include "Views/ViewTimeSetup.hpp"
#include "Views/ViewTime.hpp"
#include "Views/ViewAlarmsStatus.hpp"
#include "Views/ViewAlarmSettings.hpp"

#include "SerialPrintAssert.h"

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
    if (nullptr != ViewTime::getInstance())
    {
        ViewTime::getInstance()->setLcd(lcd);
        ViewTime::getInstance()->setModel(model);
    }

    rApplication.addThread(ViewTime::getInstance());
    rApplication.addThread(ViewMenu::getInstance());
    rApplication.addThread(ViewTimeSetup::getInstance());
    rApplication.addThread(ViewConfirmationQuestion::getInstance());
    rApplication.addThread(ViewDateSetup::getInstance());
    rApplication.addThread(ViewAlarmsStatus::getInstance());
    rApplication.addThread(ViewAlarmSettings::getInstance());

    // Then the keyboard controller...
    rApplication.addThread(KeyboardController::getInstance());

    // And then the application controller.
    rApplication.addThread(ModuleController::getInstance());
    // Now created modules are injected to the application controller (dependency injection).

    if (nullptr != ModuleController::getInstance())
    {
        ModuleController::getInstance()->setKeyboardController(KeyboardController::getInstance());

        ModuleController::getInstance()->addView(ViewTime::getInstance());
        ModuleController::getInstance()->addView(ViewMenu::getInstance());
        ModuleController::getInstance()->addView(ViewTimeSetup::getInstance());
        ModuleController::getInstance()->addView(ViewConfirmationQuestion::getInstance());
        ModuleController::getInstance()->addView(ViewDateSetup::getInstance());
        ModuleController::getInstance()->addView(ViewAlarmsStatus::getInstance());
        ModuleController::getInstance()->addView(ViewAlarmSettings::getInstance());

        ModuleController::getInstance()->addExtendedView(ViewMenu::getInstance()->getViewId(), ViewMenu::getInstance());
        ModuleController::getInstance()->addExtendedView(ViewTimeSetup::getInstance()->getViewId(), ViewTimeSetup::getInstance());
        ModuleController::getInstance()->addExtendedView(ViewDateSetup::getInstance()->getViewId(), ViewDateSetup::getInstance());
        ModuleController::getInstance()->addExtendedView(ViewAlarmsStatus::getInstance()->getViewId(), ViewAlarmsStatus::getInstance());

        ModuleController::getInstance()->setModel(model);
        ModuleController::getInstance()->setModelState(model);
    }
}
