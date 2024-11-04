#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setupDisplay() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.setTextSize(1);
    display.setCursor(0, 0);

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
}



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




// Camada de leitura de entradas
// -----------------------------

#define pinLeftButton 34
#define pinRightButton 35
#define pinNoButton 32
#define pinYesButton 33



void setupEntradas() {
    pinMode(pinLeftButton, INPUT);
    pinMode(pinRightButton, INPUT);
    pinMode(pinNoButton, INPUT);
    pinMode(pinYesButton, INPUT);
}



int leftButton = LOW;
int rightButton = LOW;
int noButton = LOW;
int yesButton = LOW;

void lerEntradas() {
    int prev_leftButton = leftButton;
    int prev_rightButton = rightButton;
    int prev_noButton = noButton;
    int prev_yesButton = yesButton;

    leftButton = digitalRead(pinLeftButton);
    rightButton = digitalRead(pinRightButton);
    noButton = digitalRead(pinNoButton);
    yesButton = digitalRead(pinYesButton);

    if (prev_leftButton == LOW and leftButton == HIGH) {
        onLeftButtonPressed();
    }

    if (prev_rightButton == LOW and rightButton == HIGH) {
        onRightButtonPressed();
    }

    if (prev_noButton == LOW and noButton == HIGH) {
        onNoButtonPressed();
    }

    if (prev_yesButton == LOW and yesButton == HIGH) {
        onYesButtonPressed();
    }
}






void setup() {
    Serial.begin(115200);
    setupDisplay();
    setupEntradas();
}

void loop() {

    lerEntradas();
    displayUI();

    delay(50);

}

