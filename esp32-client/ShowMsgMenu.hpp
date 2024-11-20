#ifndef SHOW_MSG_MENU_HPP
#define SHOW_MSG_MENU_HPP

#include "Events.hpp"
#include "Menu.hpp"
#include "Display.hpp"


class ShowMsgMenu : public Menu {
public:

    // Construtor
    ShowMsgMenu(Adafruit_SSD1306* display) {
        this->display = display;
    }

    void displayUI() {
        /* Função que printa a UI no display
         * Deve ser executada no loop. */
        display->clearDisplay();

        display->setTextColor(SSD1306_WHITE);
        display->setTextSize(2);

        // Mostrar mensagem
        display->setCursor(0, 0);
        display->println(F("Show Message Menu"));

        display->display();
    }

    void recvEvent(Event event) {}

private:
    Adafruit_SSD1306 *display;

};




#endif // !SHOW_MSG_INTERFACE_HPP
