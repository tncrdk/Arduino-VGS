void setup() {
  Serial.begin(9600);
  
  for(int base = 1; base <= 20; base++){
    for(int i = 1; i <= 10; i++){
      Serial.print(String(base*i) + " ");
    }
    Serial.println();
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
