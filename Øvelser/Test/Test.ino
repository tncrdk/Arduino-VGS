boolean pins[] = {13, 12, 11, 10, 9, 8};
boolean button = false;
int index = 0;

void setup() {
    for (int i = 0; i <= sizeof(pins); i++) {
        pinMode(i, OUTPUT);
    }
    pinMode(7, INPUT_PULLUP);
}
void loop() {
    int value = digitalRead(7);

    if (value == 0 && !button) {
        button = !button;
        
        if (index > sizeof(pins)) {
            index = 0;
            digitalWrite(index, 1);
            digitalWrite(sizeof(pins), 0);
        }
        else {
            skifte_lys(index);
        }
        
        index++;
        delay(2);
    }

    else if (value == 1 && button) {
        button = !button;
    }
}

void skifte_lys(int pin) {
    digitalWrite(pins[pin], 1);
    digitalWrite(pins[pin-1], 0);
}