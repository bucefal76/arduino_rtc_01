#ifndef RTC01_APPLICATION_BUILDER_HPP
#define RTC01_APPLICATION_BUILDER_HPP

#include "ModuleApplicationBuilderIf.hpp"

class RtcDateTime;

class Rtc01ApplicationBuilder : public ModuleApplicationBuilderIf
{
public:
    Rtc01ApplicationBuilder();

    virtual void buildApplication(ModuleApplicationIf &rApplication);

private:
    void setupThreads(ModuleApplicationIf &rApplication);

    void initalizeRct();

    void printDateTime(const RtcDateTime &dt);
};

#endif