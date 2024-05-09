#ifndef MODULE_APPLICATION_BUILDER_HPP
#define MODULE_APPLICATION_BUILDER_HPP

#include <RtcDS1302.h>
#include <ThreeWire.h>

/*

*/

class ModuleApplicationIf;

class ModuleApplicationBuilder
{
public:
    virtual void buildApplication(ModuleApplicationIf &rApplication);

protected:
    void setupThreads(ModuleApplicationIf &rApplication);

    void initalizeRct();

    void printDateTime(const RtcDateTime &dt);

    // More refactor is needed, the RtcDS1202 shall go to MODEL component (I do now have it yet).
    static ThreeWire m_myWire;
    static RtcDS1302<ThreeWire> m_rtc;
};

#endif