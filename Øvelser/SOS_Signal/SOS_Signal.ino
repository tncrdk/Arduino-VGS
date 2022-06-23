void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 2; i++){
    digitalWrite(12, HIGH);
    delay(200);
    digitalWrite(12, LOW);
    delay(200);
  }
   for (int i = 0; i <= 2; i++){
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
    delay(500);
  }
   for (int i = 0; i <= 2; i++){
    digitalWrite(12, HIGH);
    delay(200);
    digitalWrite(12, LOW);
    delay(200);
  }
    delay(2000);
}
