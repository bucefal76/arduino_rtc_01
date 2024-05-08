#ifndef RTC01_APPLICATION_BUILDER_HPP
#define RTC01_APPLICATION_BUILDER_HPP

#include "ModuleApplicationBuilder.hpp"

/*
    The class implements product-specific configuration code.
    Here the threads are added for application execution.
    Each product built on this common code base shall have its implementation of this file.
*/

class Rtc01ApplicationBuilder : public ModuleApplicationBuilder
{
public:
    Rtc01ApplicationBuilder();

    virtual void buildApplication(ModuleApplicationIf &rApplication);

private:
    void setupThreads(ModuleApplicationIf &rApplication);
};

#endif