void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int a = random(-100, 101);
  if (a == 0) {
    Serial.println("Tallet er 0!");
  }
  else if (a > 0 and a < 50){
    Serial.println("Tallet er mindre enn 50, men større enn null");
  }
  else if (a == 50) {
    Serial.println("Tallet er 50!");  
  }
  else if (a > 50) {
    Serial.println("Tallet er større enn 50");
  }
  else {
    Serial.println("Tallet er mindre enn 0");
  }
  delay(500);
}
