#include "Controller/States/StateBase.hpp"
#include "ViewIf.hpp"
#include "ViewExtendedIf.hpp"
#include "SerialPrintAssert.h"
#include "ModuleModelIf.hpp"
#include "ModuleModelStateIf.hpp"

StateBase *StateBase::m_pCurrentState = nullptr;
std::map<uint8_t, ViewIf *> StateBase::m_Views;
std::map<uint8_t, ViewExtendedIf *> StateBase::m_ExtendedViews;
ModuleModelIf *StateBase::m_pModel = nullptr;
ModuleModelStateIf *StateBase::m_pModelState = nullptr;

void StateBase::processButton(const KeyboardControllerIf::ButtonCode button)
{
}

void StateBase::addView(ViewIf *pView)
{
    RUNTIME_PTR_CHECK(pView);
    m_Views[pView->getViewid()] = pView;
}

void StateBase::addExtendedView(const uint8_t viewId, ViewExtendedIf *pExtendedView)
{
    RUNTIME_PTR_CHECK(pExtendedView);
    m_ExtendedViews[viewId] = pExtendedView;
}

void StateBase::setModel(ModuleModelIf *pModel)
{
    m_pModel = pModel;
}

void StateBase::setModelState(ModuleModelStateIf *pModelState)
{
    m_pModelState = pModelState;
}

StateBase *StateBase::getCurrentState()
{
    return m_pCurrentState;
}

void StateBase::setCurrentState(StateBase *state)
{
    m_pCurrentState = state;
}

void StateBase::transitToState(StateBase *pNexState)
{
    m_pCurrentState->exit();

    m_pCurrentState = pNexState;

    m_pCurrentState->enter();
}

ViewIf *StateBase::getView(const uint8_t viewId) const
{
    ViewIf *pView = m_Views[viewId];
    RUNTIME_PTR_CHECK(pView);
    return pView;
}

ViewExtendedIf *StateBase::getExtendedView(const uint8_t viewId) const
{
    ViewExtendedIf *pExtendedView = m_ExtendedViews[viewId];
    RUNTIME_PTR_CHECK(pExtendedView);
    return pExtendedView;
}