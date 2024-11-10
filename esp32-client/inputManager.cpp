
class InputManager {
public:
    const int pinLeftButton = 34;
    const int pinRightButton = 35;
    const int pinNoButton = 32;
    const int pinYesButton = 33;

    InputManager();

    void setup() {
        pinMode(pinLeftButton, INPUT);
        pinMode(pinRightButton, INPUT);
        pinMode(pinNoButton, INPUT);
        pinMode(pinYesButton, INPUT);
    }

    void processInput() {
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

private:
    int leftButton;
    int rightButton;
    int noButton;
    int yesButton;
};
