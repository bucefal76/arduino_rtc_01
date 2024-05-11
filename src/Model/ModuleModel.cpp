#include "Model/ModuleModel.hpp"

ModuleModel *ModuleModel::getInstance()
{
    return nullptr;
}

bool ModuleModel::isDateTimeValid() const
{
    return false;
}

DateTime ModuleModel::getDateTime() const
{
    DateTime r(1,1,1,1,1,1);
    return r;
}

void ModuleModel::setDateTime(const DateTime &dt)
{
}
