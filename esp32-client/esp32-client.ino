
#include "InputManager.hpp"


// Edição de caracteres
// ----------------------------

#define TAM_MSG 32

char mensagem[TAM_MSG] = "";
int cursor = 0;
int clock_reference = 0;

void displayUI() {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    // Mostrar mensagem
    display.setCursor(0, 0);
    for (int i = 0; i < TAM_MSG; i++) {
        display.setTextColor(SSD1306_WHITE);
        if (i == cursor && ( millis() - clock_reference )/500 % 2 == 0 ) {
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        }

        display.print(mensagem[i]);
    }


    display.display();
}


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
    if (cursor == 0) {
        cursor = TAM_MSG - 1;
        return;
    }
    cursor--;
}


void avancarCursor() {
    if (cursor == TAM_MSG - 1) {
        cursor = 0;
        return;
    }
    cursor++;
}


void onLeftButtonPressed() {
    letraAnterior();
}

void onRightButtonPressed() {
    proximaLetra();
}

void onNoButtonPressed() {
    cursor--;
    clock_reference = millis();
}

void onYesButtonPressed() {
    cursor++;
    clock_reference = millis();
}

void onYesButtonHolded() {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);

    // Mostrar mensagem
    display.setCursor(32, 24);
    display.print("YES HOLDED!");

    display.display();
}




// Camada de leitura de entradas
// -----------------------------

InputManager inputManager;

void setup() {
    Serial.begin(115200);
    setupDisplay();

    inputManager.onLeftButtonPressed = &onLeftButtonPressed;
    inputManager.onRightButtonPressed = &onRightButtonPressed;
    inputManager.onNoButtonPressed = &onNoButtonPressed;
    inputManager.onYesButtonPressed = &onYesButtonPressed;
    inputManager.onYesButtonHolded = &onYesButtonHolded;

    inputManager.setup();

}

void loop() {

    inputManager.processInput();
    displayUI();

    delay(50);
}

