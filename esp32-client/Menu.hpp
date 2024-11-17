#ifndef MENU_HPP
#define MENU_HPP

#include "Events.hpp"


class Menu {
public:

    virtual void displayUI() {}

    virtual void recvEvent(Event) {}
};


#endif // !MENU_HPP
