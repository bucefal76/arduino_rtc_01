
This is a Real Time Clock with the use of Arduino UNO, RTC DS1302 and 16x2 LCD.
- Displays time and date.
- Allows to set up time manually with the keyboard.
- Allows to set up the date manually with the keyboard.

# Goal

The goal is to develop a clock application based on the Controller-View architectural pattern.
The Views are responsible for showing messages on the LCD, and the KeyboardController (refer to KeyboardControllerIf) interprets pressed keys.
The ModuleController manages the flow of control. To simplify things further (or make it more complex),
the ModuleController uses a basic state machine under the hood for flow control.

## Benefits

The benefits of this architecture are:
- It is very easy to extend the clock with new features without modification of the existing functionality(existing files).
- Single files with View or State implementation are very short and very simple to understand.
- If you have seen one State/View then you know how to create another one to extend functionality.

## Downsides

- The existence of multuple small objects with VTABLES requires some extra amount of data memory.
- Late binding (virtual method calls) is slow. but this is not a fast application.

# Dependencies

- LiquidCrystal.h
- RtcDS1302.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- ThreeWire.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- vector by ArduinoSTL (https://github.com/mike-matera/ArduinoSTL?utm_source=platformio&utm_medium=piohome)

# Wiring

See the ModuleConfig.hpp file.

# To do

- An alarm setup could be nice to have.
- Some architectural fixes could be nice to do. Stil need to do more refactor to get generic framework.
- ???

# Resources

RAM:   [====      ]  37.8% (used 775 bytes from 2048 bytes)
Flash: [======    ]  55.9% (used 18034 bytes from 32256 bytes)


