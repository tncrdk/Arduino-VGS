int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 11;
//Pin connected to DS of 74HC595
int dataPin = 10;



const int GameLength = 30;


//VARIABLES

bool Result;
volatile bool DoYouWantToReset = false;

int Guess;
int Answerstreak;
int TimeOfLastReset = 0;

byte ShiftOutByte1 = B00000000;   // Første byte å skifte ut
byte ShiftOutByte2 = B00000000;   // Andre byte å skifte ut

int System[GameLength][2];      // Array med alle koordinatene som skal vises
int System_Templates[] = {1};


// (2, 3)

int bin1 = B00000000;
int bin2 = B10000010;

int test = B00000000;

void setup() {
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
Serial.begin(9600);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, 130);
  digitalWrite(latchPin, HIGH);

  Serial.println(64);
  Serial.println(256);
  Serial.println("------------------------");

  Conversion_Coordinates(0, 0);
  Serial.println(ShiftOutByte1);
  Serial.println(ShiftOutByte2);
  Serial.println("----------------");
}

void loop() {
 RegularJumpHorizontal(); 
}


void Conversion_Coordinates(int x, int y) {
  // Convert from coordinates to binary
  ShiftOutByte1 = B00000000;
  ShiftOutByte2 = B00000000;

  bitSet(ShiftOutByte2, (7-y));

  if (x < 2) {
    bitSet(ShiftOutByte2, (1-x));
  } else {
    bitSet(ShiftOutByte1, (9-x)); // 7-(x-2)
  }
}

int RegularJumpHorizontal() {
  int i = 0;
  int jump = random(1, 7);
  int x_coor = 0;
  int y_coor = 0;

  do {
    Conversion_Coordinates(x_coor, y_coor);
    System[i][0] = ShiftOutByte2;
    System[i][1] = ShiftOutByte1;
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, ShiftOutByte1);
    shiftOut(dataPin, clockPin, LSBFIRST, ShiftOutByte2);
    digitalWrite(latchPin, HIGH);
    
    Serial.println(ShiftOutByte1);
    Serial.println(ShiftOutByte2);
    Serial.println(x_coor);
    Serial.println(y_coor);
    Serial.println("--------------------------");

    x_coor += jump;

    if(x_coor > 9) {
      x_coor -= 10;
      y_coor += 1;
    }

    if(y_coor > 4) {
      y_coor -= 5;
    }

    i++;
    delay(1000);

  } while(i < GameLength);
}
