
int Fac(int x){
  if(x == 1 || x == 0){
    return 1;
  }
  else{
    return x*Fac(x-1);
  }
}

void setup() {
  Serial.begin(9600);
  int x = Fac(17);
  Serial.println(x);
}

void loop() {

}
