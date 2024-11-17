#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <Arduino.h>
#include "Events.hpp"

class InputManager {
public:

    // Pins
    const int pinLeftButton = 34;
    const int pinRightButton = 35;
    const int pinNoButton = 32;
    const int pinYesButton = 33;


    // Variaveis dos Hooks
    void (*eventHandler)(Event);

    void emit(Event event) {
        eventHandler(event);
    }


    // Constructor
    InputManager() {};

    void setup() {
        /* Função de setup que inicializa os pinos como entrada.
         * Deve ser executada no setup do arduino. */

        pinMode(pinLeftButton, INPUT);
        pinMode(pinRightButton, INPUT);
        pinMode(pinNoButton, INPUT);
        pinMode(pinYesButton, INPUT);
    }

    void processInput() {
        /* Função que realiza a leitura das entradas do arduino e chama as funções adequadas.
         * Deve ser executada no loop do arduino. */

        int prev_leftButton = leftButton;
        int prev_rightButton = rightButton;
        int prev_noButton = noButton;
        int prev_yesButton = yesButton;

        leftButton = digitalRead(pinLeftButton);
        rightButton = digitalRead(pinRightButton);
        noButton = digitalRead(pinNoButton);
        yesButton = digitalRead(pinYesButton);


        // Apertou o botão Left
        if (prev_leftButton == LOW and leftButton == HIGH) {
            emit(LEFT_BUTTON_PRESSED);
        }

        // Apertou o botão Right
        if (prev_rightButton == LOW and rightButton == HIGH) {
            emit(RIGHT_BUTTON_PRESSED);
        }

        // Apertou o botão No
        if (prev_noButton == LOW and noButton == HIGH) {
            emit(NO_BUTTON_PRESSED);
        }

        // Apertou o botão Yes
        if (prev_yesButton == LOW and yesButton == HIGH) {
            holdTime = millis();
        }

        // Soltou o botão Yes
        if (prev_yesButton == HIGH and yesButton == LOW) {
            int prev_holdTime = holdTime;
            holdTime = millis();

            // Apertou 
            if (holdTime - prev_holdTime < 1000) {
                emit(YES_BUTTON_PRESSED);

            } else {
            // Segurou
                emit(YES_BUTTON_HOLDED);
            }
        }
    }

private:
    int leftButton;
    int rightButton;
    int noButton;
    int yesButton;
    int holdTime;
};

#endif // !INPUT_MANAGER_HPP
