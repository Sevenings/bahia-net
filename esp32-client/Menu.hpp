#ifndef MENU_HPP
#define MENU_HPP

#include "Events.hpp"


class Menu {
public:

    virtual void displayUI() = 0; 

    virtual void recvEvent(Event) = 0;
};


#endif // !MENU_HPP
