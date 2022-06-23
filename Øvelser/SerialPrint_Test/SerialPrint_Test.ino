int a = 0;
int b = 1;
int n = b;
int AntallTall = 100;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= AntallTall + 1; i++) {
    Serial.println(a);
    n = b;
    b = b + a;
    a = n;
    delay(100);
  }
}

void loop() {
}
