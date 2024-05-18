#include "Controller/States/StateNewDateConfirmation.hpp"
#include "Controller/States/StateDisplayingTime.hpp"
#include "ViewIf.hpp"
#include "ModuleConfig.hpp"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"
#include "Model/DateTime.hpp"

StateNewDateConfirmation StateNewDateConfirmation::m_Instance;

StateBase *StateNewDateConfirmation::getInstance()
{
    return &m_Instance;
}

StateNewDateConfirmation::StateNewDateConfirmation()
{
}

void StateNewDateConfirmation::processButton(const KeyboardControllerIf::ButtonCode button)
{
    if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_NEXT == button)
    {
        setNewDate();

        trasitToState(StateDisplayingTime::getInstance());
    }
    else if (KeyboardControllerIf::ButtonCode::BUTTON_CODE_BACK == button)
    {
        trasitToState(StateDisplayingTime::getInstance());
    }
}

void StateNewDateConfirmation::setNewDate()
{
    const DateTime now = m_pModelState->getDateTime();

    DateTime modifiedTimeDate(m_Year,
                              m_Month,
                              m_Day,
                              now.getHour(),
                              now.getMinute(),
                              now.getSecond());

    m_pModel->setDateTime(modifiedTimeDate);
}

void StateNewDateConfirmation::enter()
{
    getView(VIEW_ID_CONFIRMATION_VIEW)->enable();
}

void StateNewDateConfirmation::exit()
{
    getView(VIEW_ID_CONFIRMATION_VIEW)->disable();
}