#include "Menu.hpp"
#include "InputManager.hpp"
#include "Display.hpp"
#include "EditMsgMenu.hpp"
#include "ShowMsgMenu.hpp"
#include "Events.hpp"
#include "Global.hpp"

InputManager inputManager;
EditMsgMenu editMsgMenu(&display);
ShowMsgMenu showMsgMenu(&display);


void eventHandler(Event event) {
    Global::selectedMenu->recvEvent(event);
}


void setup() {
    Serial.begin(115200);

    // Realiza o setup do Display Oled
    setupDisplay();

    // Seleciona o menu inicial
    Menu* Global::selectedMenu = &editMsgMenu;

    // Configurando o InputManager
    inputManager.eventHandler = &eventHandler;
    inputManager.setup();
}

void loop() {
    inputManager.processInput();
    Global::selectedMenu->displayUI();

    delay(50);
}

