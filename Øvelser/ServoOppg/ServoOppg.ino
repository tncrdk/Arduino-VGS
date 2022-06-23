#include <Servo.h>;

Servo myservo;

boolean button = false;

void setup() {
  pinMode(13, INPUT_PULLUP);
  myservo.attach(9);
  myservo.write(20);
}

void loop() {
  int value = digitalRead(13);

  if (value == 0 && !button) {
    button = !button;
    for (int i = 1; i <= 2; i++) {
      myservo.write(160);
      delay(300);
      myservo.write(20);
      delay(300);
    }
  }

  if (value == 1 && button) {
    button = !button;
  }
}
