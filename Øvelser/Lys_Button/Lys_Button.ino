boolean trykket = false;
boolean lys = false;
boolean lys2 = true;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  int verdi = digitalRead(2);
  // Variabelen har verdien 1 når knappen ikke er trykket
  // Variabelen har verdien 0 når knappen er trykket
  if (verdi == LOW && !trykket)
  {
    trykket = !trykket; //VIKTIG! "Snur" verdien.
    // Kode som utføres i det knappen trykkes ned.
    lys = !lys; //Bytter mellom true/false eller HIGH/LOW.
    lys2 = !lys2;
    digitalWrite(13, lys);
    digitalWrite(12, lys2);
  }
  else if (verdi == HIGH && trykket)
  {
    trykket = !trykket; //VIKTIG! "Snur" verdien.
    // Kode som utføres i det knappen slippes opp.
  }
  delay(2); //For stabilitet.
}
