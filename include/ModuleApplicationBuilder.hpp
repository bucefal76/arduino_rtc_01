#ifndef MODULE_APPLICATION_BUILDER_HPP
#define MODULE_APPLICATION_BUILDER_HPP

#include "ModuleApplicationBuilderIf.hpp"
#include <RtcDS1302.h>
#include <ThreeWire.h>

/*
    Every product-specific application builder needs some basic, generic functionality.
    For example, setup for the RTC hardware unit.
*/

class ModuleApplicationBuilder : public ModuleApplicationBuilderIf
{
protected:
    void initalizeRct();

    void printDateTime(const RtcDateTime &dt);

    // More refactor is needed, the RtcDS1202 shall go to MODEL component (I do now have it yet).
    static ThreeWire m_myWire;
    static RtcDS1302<ThreeWire> m_rtc;
};

#endif