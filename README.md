# Introduction

This is a Real Time Clock that uses Arduino UNO, RTC DS1302, PCF8574, and 16x2 LCD.
- Displays time and date - DONE.
- Allows to set up time manually with the keyboard - DONE.
- Allows to set up the date manually with the keyboard - DONE.
- Allows to set up the ON/OFF alarms on IO control lines. - DONE.

In this case, 8 control IO lines are provided by the i2C to IO PCF8574 extender.

## Goal

The software solution follows the Model View Controller architectural pattern.
The Views are responsible for displaying messages on the LCD.
The ModuleController manages the flow of control, while the Model handles the Real-time clock complexity of the hardware.
The objective is to create code that can be extended without modification to accommodate new functionalities.

## Benefits

The benefits of this architecture are:
- It is very easy to extend the clock with new features without modification of the existing functionality(existing files).
- Single files with View or State implementation are concise and easy to understand.
- If you have seen one State/View then you know how to create another one to extend functionality.

## Downsides

- The existence of multiple small objects with VTABLES requires some extra amount of data memory.
- Late binding (virtual method calls) is slow. but this is not a fast application.
- Some strange problems and instability after exceeding RAM allocation by 55% were caused by an unknown nature.

# Architecture

## Components diagram
A simplified diagram presents the main components of the software architecture.

- Controller - controls the software behavior. The details of the software behavior are defined by the State Machine (component States). ModuleControler captures the input from the KeyboardControler and then passes it to the State Machine.
- States of the State Machine give requests to the Views component. In the Views component, there are multiple - Views adapted for selected states of State Machine (for example, view to set new time).
- Finally, the Model component encapsulates the hardware Real real-time clock (RTC) details. The Views use Model to get the date and time, while Controler can alter the Model (RTC) setting.


![PlantUML model](https://www.plantuml.com/plantuml/png/TPC_JyCm4CNtV8fJfp9O_653g2hG1I4wq0fcarnBX6D7ZgE2GhyxxiMrczZD45bvltlsktFcZU7Qj9N8Qfv_yot2GrsBCkUcL1Aw3En3hr8Qr1kU8xoNk7lUZ3w-gg8LQDyeh9QHUdHyKj9e9GHgw7fbMFk2lv-Awo9mri9pkQfg9L4QjqUWOYIs2f1RX6DDLeORR2R06-YNBk-eOhp78s-G-3CwQKjlCg1yBTp_iKBj93lYTu0_1cNHU7wVXTeu5x2sPkdMkU91LfeCHQKLTESRJ412VJFvOdLzUtMJqDPV6l6ZrEXjJytehCChaiQe8xEma-rAsw1dmtTcAR-derAn3tUrdp2jeFD3IOxr0CKIrIvzZISfbliTOjLFc8ZnWFVzCUnvJqTA_DHPkbYnFkoam_fyBAt29MpHBBZ1TLdXz2BhcTWwTQ6SHwA6pToFuuYvZTTMuXy0)

## Dependencies

- LiquidCrystal.h
- RtcDS1302.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- ThreeWire.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)

## Wiring

See the ModuleConfig.hpp file.

# To do

- More testing including a UT.
- Watchdog support.
- Suport for Days of the week.
- Cleaning EEPROM settings when the battery is bad or at the user requst.
- Initialization of the IO lines to ON/OFF by the user.

# Resources

RAM:   [=======   ]  65.0% (used 1332 bytes from 2048 bytes)

Flash: [========  ]  82.2% (used 26526 bytes from 32256 bytes)