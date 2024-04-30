#ifndef MENU_VIEW__IF_HPP
#define MENU_VIEW_IF_HPP

class MenuViewIf
{
public:

    virtual void setTitle(const char* title) = 0;
    virtual void setContent(const char* content) = 0;
};

#endif