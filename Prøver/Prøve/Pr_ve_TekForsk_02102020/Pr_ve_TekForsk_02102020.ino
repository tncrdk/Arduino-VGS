void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  int ARead = analogRead(A0);
  float Pause = (ARead * 1.95) + 2000;
  if (Pause < 2660){
    Pause = 2000;
  }
  else if (Pause < 3300){
    Pause = 3000;
  }
  else {
    Pause = 4000;
  }
  Serial.println(Pause);
  
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(Pause);
  digitalWrite(12, LOW);
  
}
