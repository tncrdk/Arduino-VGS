int dimmer;
int timer;
int step = 0;
int limit = 2000;
volatile bool pushed = false;


void setup() {
    pinMode(11, OUTPUT);  //Led-lys
    pinMode(2, INPUT_PULLUP);  //Knappen
    attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);  //Bytte mellom funksjonene bedre
}

void loop() {
    if (pushed) {
        Dim();
    }
    else if (!pushed) {
        blink();
    }
}

void Dim() {
    while (timer < limit && pushed) {
        dimmer = map(timer, 0, limit, -255, 255);
        analogWrite(11, abs(dimmer));
        timer = millis() - step;
    }
    timer = 0;
    step = millis();
}

void blink() {
    digitalWrite(11, 255);
  	delay(1000);
    digitalWrite(11, 0);
    delay(1000);
}

void interrupt() {
    pushed = !pushed;
}
