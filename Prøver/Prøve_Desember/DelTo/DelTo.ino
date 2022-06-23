#include <Servo.h>;
Servo MyServo;

int threshold = 750;
int LightLevel, Dim;
int Timer = millis();

volatile bool pushed = true;

void setup() {
    MyServo.attach(9);
    pinMode(6, OUTPUT);
    pinMode(2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), Interrupt, FALLING);  //Hvis knappen trykkes, vil pinnen forandres og Interrupt vil bli kalt
                                                                   //vil pushed ha forandret seg
}

void loop() {
    LightLevel = analogRead(0);
    Persienner(LightLevel);
    
    if (pushed) {
        Dimmer(LightLevel);
    }
    else if (!pushed) {
        digitalWrite(6, HIGH);
    }
}

void Persienner(int LightLevel) {
    if (LightLevel > threshold) {
        MyServo.write(160);
    }
    else {
        MyServo.write(20);
    }
}

void Dimmer(int LightLevel) {
    Dim = map(LightLevel, 400, 950, 255, 0);  //400-950 fungerte på pulten, men hvis det blir lysere enn 950 vil det reverseres igjen. Da må du øke grensen(950-->)
    analogWrite(6, Dim);
}

void Interrupt() {
    if (millis()-Timer > 800) {  //Tar tiden mellom hver gang Interrupt har blitt kalt. Gjør knappen mer stabil. Når knappen er nede kan signalene være kaotiske. 
        pushed = !pushed;        // og interupt kan bli kalt mange ganger på kor tid. Det betyr at du må vente omtrent ett sekund mellom hvert trykk på knappen.
        Timer = millis();
        delay(100);
    }
}
