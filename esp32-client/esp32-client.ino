#include "Menu.hpp"
#include "InputManager.hpp"
#include "Display.hpp"
#include "Events.hpp"
#include "Global.hpp"
#include "Routes.hpp"

InputManager inputManager;

void eventHandler(Event event) {
    Navigator::selectedMenu->recvEvent(event);
}


void setup() {
    Serial.begin(115200);

    // Realiza o setup do Display Oled
    setupDisplay();

    // Configurando o InputManager
    inputManager.eventHandler = &eventHandler;
    inputManager.setup();
}

void loop() {
    inputManager.processInput();
    Navigator::selectedMenu->displayUI();

    delay(50);
}

