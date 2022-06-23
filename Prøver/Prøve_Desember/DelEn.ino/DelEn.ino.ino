#include <Servo.h>;
Servo MyServo;

int threshold = 750;
int LightLevel, Dim;

volatile bool pushed = true;

void setup() {
    MyServo.attach(9);
    pinMode(6, OUTPUT);
    pinMode(2, INPUT_PULLUP);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(2), Interupt, RISING);  //Hvis knappen trykkes, vil pinnen forandres og Interupt vil bli kalt
                                                                   //vil pushed ha forandret seg
}

void loop() {
    LightLevel = analogRead(0);
    Persienner(LightLevel);
    
    if (pushed) {
        Dimmer(LightLevel);
        
        delay(200);
    }
    else if (!pushed) {
        digitalWrite(6, HIGH);
        delay(200);
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
    Serial.println(LightLevel);
    Dim = map(LightLevel, 400, 950, 255, 0);  //400-950 fungerte på pulten, men hvis det blir lysere enn 950 vil det reverseres igjen. Da må du øke grensen(950-->)
    analogWrite(6, Dim);
}

void Interupt() {
    pushed = !pushed;
    delay(100);
}
