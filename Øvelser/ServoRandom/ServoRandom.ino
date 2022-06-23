#include <Servo.h>;

boolean button = false;
Servo myservo;

void setup() {
    pinMode(13, INPUT_PULLUP);
    myservo.attach(9);
    randomSeed(analogRead(A0));
    Serial.begin(9600);
}
void loop() {
    int value = digitalRead(13);

    if (value == 0 && !button) {
        button = !button;
        int terning = random(1, 7);
        int ranAns = map(terning, 1, 7, 20, 160);
        myservo.write(ranAns);
        Serial.println(ranAns);
        Serial.println(terning);
        delay(100);
    }
    else if (value == 1 && button) {
        button = !button;
        delay(100);
    }
}
