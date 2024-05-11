
# Introduction

This is a Real Time Clock with the use of Arduino UNO, RTC DS1302 and 16x2 LCD.
- Displays time and date.
- Allows to set up time manually with the keyboard.
- Allows to set up the date manually with the keyboard.

## Goal

The software solution follows the Model View Controller architectural pattern.
The Views are responsible for displaying messages on the LCD.
The ModuleController manages the flow of control, while the Model handles the Real-time clock complexity of the hardware.
The objective is to create code that can be extended without modification to accommodate new functionalities.

## Benefits

The benefits of this architecture are:
- It is very easy to extend the clock with new features without modification of the existing functionality(existing files).
- Single files with View or State implementation are very short and very simple to understand.
- If you have seen one State/View then you know how to create another one to extend functionality.

## Downsides

- The existence of multuple small objects with VTABLES requires some extra amount of data memory.
- Late binding (virtual method calls) is slow. but this is not a fast application.

# Architecture

## Components diagram
A simplified diagram presents the main components of the software architecture. Note that formal interfaces are not listed here. 

![PlantUML model](https://www.plantuml.com/plantuml/png/TPC_JyCm4CNtV8fJfp9O_653g2hG1I4wq0fcarnBX6D7ZgE2GhyxxiMrczZD45bvltlsktFcZU7Qj9N8Qfv_yot2GrsBCkUcL1Aw3En3hr8Qr1kU8xoNk7lUZ3w-gg8LQDyeh9QHUdHyKj9e9GHgw7fbMFk2lv-Awo9mri9pkQfg9L4QjqUWOYIs2f1RX6DDLeORR2R06-YNBk-eOhp78s-G-3CwQKjlCg1yBTp_iKBj93lYTu0_1cNHU7wVXTeu5x2sPkdMkU91LfeCHQKLTESRJ412VJFvOdLzUtMJqDPV6l6ZrEXjJytehCChaiQe8xEma-rAsw1dmtTcAR-derAn3tUrdp2jeFD3IOxr0CKIrIvzZISfbliTOjLFc8ZnWFVzCUnvJqTA_DHPkbYnFkoam_fyBAt29MpHBBZ1TLdXz2BhcTWwTQ6SHwA6pToFuuYvZTTMuXy0)

## Dependencies

- LiquidCrystal.h
- RtcDS1302.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- ThreeWire.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- vector and map by ArduinoSTL (https://github.com/mike-matera/ArduinoSTL?utm_source=platformio&utm_medium=piohome)

## Wiring

See the ModuleConfig.hpp file.

# To do

- An alarm setup could be nice to have.
- Improve documentation.
- The ExtendedViews interfaces looks like not best idea, need to clean this up.
- ???

# Resources

RAM:   [====      ]  38.4% (used 787 bytes from 2048 bytes)
Flash: [======    ]  59.8% (used 19274 bytes from 32256 bytes)


