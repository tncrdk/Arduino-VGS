int timer; 
int dimmer;
int step = 0;
int limit = 2000;

void setup() {
    pinMode(11, OUTPUT);
}

void loop() {
    while (timer < limit) {
        dimmer = map(timer, 0, limit, -255, 255);
        analogWrite(11, abs(dimmer));
        timer = millis() - step;
    }
    timer = 0;
    step = millis();
}
