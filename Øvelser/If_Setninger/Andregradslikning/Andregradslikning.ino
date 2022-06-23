void setup() {
  Serial.begin(9600);
  float a = 2;
  float b = 4;
  float c = -6;
  
  float m = (-b)/(2*a);
  float c1 = c/a;
  
  float d2 = pow(m, 2)-c1;

  if (d2 < 0) {
    float d = sqrt(abs(d2));
    Serial.print("rot1 = ");
    Serial.print(m);
    Serial.print(-d);
    Serial.println("i");
    Serial.print("rot2 = ");
    Serial.print(m);
    Serial.print("+");
    Serial.print(d);
    Serial.println("i");
    }
  else {
    float d = sqrt(d2);
    float rot1 = m - d;
    float rot2 = m + d;

    Serial.print("rot1 = ");
    Serial.println(rot1);
    Serial.print("rot2 = ");
    Serial.println(rot2);
  } 
}
void loop() {
  
}
