int pins[] = {13, 12, 11, 10, 9};
bool button[] = {false, false, false, false, false};

int Limit = 300;
int verdi;
int start;
int timer;
bool Success = false;

void setup() {
    for (int i; i < sizeof(pins); i++) {
        pinMode(i, INPUT_PULLUP);
    }
    Serial.begin(9600);

}

void loop() {

}

bool playmodule(int HitButton, int Index) {
    start = millis();
    while (timer < Limit) {
        verdi = digitalRead(HitButton);
        if (verdi == 0 && !button[Index]) {
            Serial.println("Du greide det");
            button[Index] = !button[Index];
            return true;
        }
        else if (verdi = 1 && button[Index]) {
            button[Index] = !button[Index];
        }
        timer = start - millis();
    }
    return false;    
}

void lose_sequence() {

}

void ReadyPlayerOneIntro(int InitButton) {
    Serial.println("Ready Player One \n Press Start to initialize your loss HAHAHA!!");
    while (!InitButton) {
        delay(0);
    }
    
}
