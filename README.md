
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

@startuml
```plantuml


package Application {
    
    interface ViewIf
    interface ModuleModelIf


    package Controller {

        interface KeyboardControllerIf

        component ModuleController
        component KeyboardController
        
        package "States" as States {
            
            component BaseState
            component StateN        

            BaseState <|-down- StateN : extends
        }


        KeyboardController -up- KeyboardControllerIf
    }

    package "Model" as Model {

        component ModuleModel
        component RtcDS1302
        component ThreeWire

        ModuleModel -up- ModuleModelIf
        ModuleModel -down-> RtcDS1302 : use
        RtcDS1302 --> ThreeWire : use
    }

    package "Views" as Views {      

        component BaseView
        component ViewN

        BaseView -up- ViewIf

        BaseView <|-down- ViewN : extends
    }    

}

Controller -down-( ViewIf : use
Controller -down-( ModuleModelIf : use
Views --( ModuleModelIf : use / getDateTime()
ModuleController -down-( KeyboardControllerIf : use
ModuleController --> States : use

```
@enduml

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


