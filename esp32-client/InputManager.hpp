#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <Arduino.h>

class InputManager {
public:

    // Pins
    const int pinLeftButton = 34;
    const int pinRightButton = 35;
    const int pinNoButton = 32;
    const int pinYesButton = 33;


    // Variaveis dos Hooks
    void (*onLeftButtonPressed)();
    void (*onRightButtonPressed)();
    void (*onNoButtonPressed)();
    void (*onYesButtonPressed)();
    void (*onYesButtonHolded)();
    

    // Funções de attach hooks
    // ----------------------------
    
    // Left Pressed
    void attachHookOnLeftButtonPressed(const auto& func) {
        onLeftButtonPressed = func;
    }

    // Right Pressed
    void attachHookOnRightButtonPressed(const auto& func) {
        onRightButtonPressed = func;
    }

    // No Pressed
    void attachHookOnNoButtonPressed(const auto& func) {
        onNoButtonPressed = func;
    }

    // Yes Pressed
    void attachHookOnYesButtonPressed(const auto& func) {
        onYesButtonPressed = func;
    }

    // Yes Holded
    void attachHookOnYesButtonHolded(const auto& func) {
        onYesButtonHolded = func;
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
            onLeftButtonPressed();
        }

        // Apertou o botão Right
        if (prev_rightButton == LOW and rightButton == HIGH) {
            onRightButtonPressed();
        }

        // Apertou o botão No
        if (prev_noButton == LOW and noButton == HIGH) {
            onNoButtonPressed();
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
                onYesButtonPressed();
            } else {
            // Soltou
                onYesButtonHolded();
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
