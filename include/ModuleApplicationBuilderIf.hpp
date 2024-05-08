#ifndef MODULE_APPLICATION_BUILDER_IF_HPP
#define MODULE_APPLICATION_BUILDER_IF_HPP

#include "ModuleApplicationIf.hpp"

class ModuleApplicationBuilderIf
{
public:
    virtual void buildApplication(ModuleApplicationIf &pApplication) = 0;
};

#endif