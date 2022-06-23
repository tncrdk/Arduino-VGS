    int alder = 17
    String fjortis = "Du er fjortis"
    String barn = "Du er et barn"
    String voksen = "Du er voksen"
    String pensjonist = "Du er pensjonist"
    String tenaaring = "Du er tenåring"
    String myndig = "Du er myndig"

void setup() {    
    if (alder >= 20){
      Serial.println("Du er voksen");
      if (alder >= 67){
        Serial.println("Du er pensjonist");
        Serial.println("Du er myndig");
    }
  }
  else if (alder < 13){
    Serial.println("Du er et barn");
  }
  else if (alder >= 13 && alder <= 19){
    Serial.println("Du er tenåring");
    if (if alder >= 18) {
      Serial.println("Du er myndig");
    }
    else if (alder <= 15) {
      Serial.println("Du er et barn");
      if (alder == 14) {
        Serial.println("Du er fjortis");
      }
    }
  }
}

void loop() {

}
