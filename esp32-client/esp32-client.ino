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


int debug_a = 0;
int debug_b = 0;
int debug_c = 0;
int debug_d = 0;

void onLeftButtonPressed() {
    debug_a++;
}

void onRightButtonPressed() {
    debug_b++;
}

void onNoButtonPressed() {
    debug_c++;
}

void onYesButtonPressed() {
    debug_d++;
}


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

    display.clearDisplay();

    display.setCursor(0, 0);
    display.setTextColor(SSD1306_WHITE);

    display.print(F("Left button: ")); display.println(debug_a);
    display.print(F("Right button: ")); display.println(debug_b);
    display.print(F("No button: ")); display.println(debug_c);
    display.print(F("Yes button: ")); display.println(debug_d);
    
    display.display();

    delay(50);

}

