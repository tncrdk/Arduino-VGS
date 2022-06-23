void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pos = analogRead(A0);
  Serial.println(pos);
  if (pos < 400) {
    digitalWrite(13, HIGH);
    delay(pos);
    digitalWrite(13, LOW);
    delay(pos); 
  }
  else {
    digitalWrite(12, HIGH);
    delay(pos);
    digitalWrite(12, LOW);
    delay(pos);
  }
}
