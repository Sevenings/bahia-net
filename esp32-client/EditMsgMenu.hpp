#ifndef EDIT_MSG_INTERFACE_HPP
#define EDIT_MSG_INTERFACE_HPP

#define TAM_MSG 21

#include "Routes.hpp"
#include "Menu.hpp"
#include "Display.hpp"
#include "Events.hpp"
#include "Routes.hpp"


class EditMsgMenu : public Menu {
public:

    // Construtor
    EditMsgMenu(Adafruit_SSD1306* display) {
        this->display = display;
    }

    void displayUI() {
        /* Função que printa a UI no display
         * Deve ser executada no loop. */
        display->clearDisplay();

        display->setTextColor(SSD1306_WHITE);
        display->setTextSize(1);

        // Mostrar mensagem
        display->setCursor(0, 0);
        display->println(F("Mensagem:"));

        for (int i = 0; i < TAM_MSG; i++) {
            display->setTextColor(SSD1306_WHITE);
            if (i == cursor && ( millis() - clock_reference )/500 % 2 == 0 ) {
                display->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
            }

            display->print(mensagem[i]);
        }
        display->display();
    }


    void recvEvent(Event event) {
        switch (event) {
            case LEFT_BUTTON_PRESSED:
                letraAnterior();
                break;

            case RIGHT_BUTTON_PRESSED:
                proximaLetra();
                break;

            case NO_BUTTON_PRESSED:
                voltarCursor();
                break;

            case YES_BUTTON_PRESSED:
                avancarCursor();
                break;

            case YES_BUTTON_HOLDED:
                Navigator::navigateTo(Navigator::SHOW_MSG_MENU);
                break;
        }
    }

private:
    char mensagem[TAM_MSG] = "";
    int cursor = 0;
    int clock_reference = 0;

    Adafruit_SSD1306 *display;

    void letraAnterior() {
        if (mensagem[cursor] < 'a' || mensagem[cursor] > 'z') {
            mensagem[cursor] = 'z';
            return;
        } 
        if (mensagem[cursor] == 'a') {
            mensagem[cursor] = ' ';
            return;
        }

        mensagem[cursor] -= 1;

    }


    void proximaLetra() {
        if (mensagem[cursor] < 'a' || mensagem[cursor] > 'z') {
            mensagem[cursor] = 'a';
            return;
        } 

        if (mensagem[cursor] == 'z') {
            mensagem[cursor] = ' ';
            return;
        }

        mensagem[cursor] += 1;

    }


    void voltarCursor() {
        clock_reference = millis();
        if (cursor == 0) {
            cursor = TAM_MSG - 1;
            return;
        }
        cursor--;
    }


    void avancarCursor() {
        clock_reference = millis();
        if (cursor == TAM_MSG - 1) {
            cursor = 0;
            return;
        }
        cursor++;
    }

};




#endif // !EDIT_MSG_INTERFACE_HPP
