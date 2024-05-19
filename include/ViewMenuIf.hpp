#ifndef MENU_VIEW__IF_HPP
#define MENU_VIEW_IF_HPP

#include "ExtendedViewIf.hpp"

/*
    An interface declares a methods to extend the view with the functionality required to display the settings menu.
*/

class ViewMenuIf : public ExtendedViewIf
{
public:
    /// @brief Set title on the menu screen.
    /// @param title
    virtual void setTitle(const char *title) = 0;
    /// @brief Set menu content.
    /// @param content
    virtual void setContent(const char *content) = 0;
};

#endif