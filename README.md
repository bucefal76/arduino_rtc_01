
This is a Real Time Clock with the use of Arduino UNO, RTC DS1302 and 16x2 LCD.

# Goal

The goal is to develop a clock application based on the Controller-View architectural pattern.
The Views are responsible for showing messages on the LCD, and the KeyboardController (refer to KeyboardControllerIf) interprets pressed keys.
The ModuleController manages the flow of control. To simplify things further (or make it more complex),
the ModuleController uses a basic state machine under the hood for flow control.

The benefits of this architecture are:
- It is very easy to extend the clock with new features without modification of the existing functionality(existing files).
- Single files with View or State implementation are very short and very simple to understand.

# Dependencies
- LiquidCrystal.h
- RtcDS1302.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)
- ThreeWire.h (https://github.com/Makuna/Rtc/blob/master/src/RtcDS1302.h)

# Wiring

See the ModuleConfig.hpp file.

# To do

- The date setup is still not completed.
- Alarm setup could be nice to have.
- Some architectural fixes could be nice to do.
- ???

