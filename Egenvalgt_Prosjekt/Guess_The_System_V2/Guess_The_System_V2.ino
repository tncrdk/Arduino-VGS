/*
  ALLE VARIABLER ER SKREVET PÅ ENGELSK FOR Å SLIPPE Æ,Ø,Å, UTEN AT JEG MÅ TENKE OVER DET
*/

// KONSTANTER

const int LatchPin = 13;
const int ClockPin = 12;
const int DataPin = 11;

const int left_button = 4;
const int right_button = 5;
const int up_button = 6;
const int down_button = 7;
const int reset_button = 2;
const int OK_button = 3;

const int OK_LED = 8;
const int Reset_LED = 9;

const int Correct_LED = A5;
const int Wrong_LED = A4;

const int GameLength = 30;
const int NumberOfSystems = 2;
const int ShowNumOfLed = 10;
const int WinAnswerstreak = 5;

// FUNKSJON-ARRAY

typedef void (*SystemFunctionPtr)();                                                                  // Lager en type som er pointer til funksjon, bruker denne typen til å lage en array med funksjon-pointere
SystemFunctionPtr System_Templates[NumberOfSystems] = {&RegularJumpHorizontal, &RegularJumpVertical}; // Array med pointere til ulike systemgeneratorer

//VARIABLER

bool StartGame = false;
bool Continue = false;
volatile bool ResetGame = false;

int Answerstreak = 0;
int GameRound = 0;
int Progression = 0;
int TimeOfLastReset = 0;

int current_x_cor = 0;
int current_y_cor = 0;

byte current_x_bin = B00000000;
byte current_y_bin = B00000000;

byte ShiftOutByte1 = B00000000; // Første byte å skifte ut
byte ShiftOutByte2 = B00000000; // Andre byte å skifte ut

int System_Coor[GameLength][2]; // Array med alle koordinatene som skal vises

// VARIABLER -> KNAPPER

int right_button_value;
int left_button_value;
int up_button_value;
int down_button_value;
int OK_button_value;

bool left_button_pushed = false;
bool right_button_pushed = false;
bool up_button_pushed = false;
bool down_button_pushed = false;
bool OK_button_pushed = false;

//----------------------------------------------

void setup()
{
  randomSeed(analogRead(A0));

  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataPin, OUTPUT);

  pinMode(OK_LED, OUTPUT);
  pinMode(Reset_LED, OUTPUT);
  pinMode(Correct_LED, OUTPUT);
  pinMode(Wrong_LED, OUTPUT);

  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(OK_button, INPUT_PULLUP);
  pinMode(reset_button, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(reset_button), Interrupt, FALLING);
}

void loop()
{
  ResetLEDs();
  MainGame();

  // RESETTE ALLE VARIABLER
  // -------------------------------------------------------------------------------
  ResetLEDs();

  Continue = false;
  ResetGame = false;
  StartGame = false;

  Answerstreak = 0;
  GameRound = 0;
  Progression = 0;
  TimeOfLastReset = 0;

  current_x_cor = 0;
  current_y_cor = 0;

  current_x_bin = B00000000;
  current_y_bin = B00000000;

  ShiftOutByte1 = B00000000; // Første byte å skifte ut
  ShiftOutByte2 = B00000000; // Andre byte å skifte ut

  // VARIABLER -> BUTTONS

  left_button_pushed = false;
  right_button_pushed = false;
  up_button_pushed = false;
  down_button_pushed = false;
  OK_button_pushed = false;

  // -------------------------------------------------------------------------------
}

int MainGame()
{
  int Rand_Choose_System = random(0, NumberOfSystems); // Velger en tilfeldig indeks
  System_Templates[Rand_Choose_System]();              // Bruker den tilfeldige indeksen til å lage et system ved å kalle funksjonen

  while (!StartGame) // Venter på at spilleren skal bli klar og starte spillet
  {
    OK_button_value = digitalRead(OK_button);

    if (OK_button_value == LOW && !OK_button_pushed)
    {
      OK_button_pushed = !OK_button_pushed;
      digitalWrite(OK_LED, HIGH);
      delay(1000);
      digitalWrite(OK_LED, LOW);
    }

    if (OK_button_value == HIGH && OK_button_pushed)
    {
      OK_button_pushed = !OK_button_pushed;
      StartGame = true;
    }
  }

  StartGame = false;

  while (Progression < ShowNumOfLed) // Viser de X første LED-lysene fra systemet slik at spilleren har noe å gå på
  {
    ShowSystemLED();
    Progression++;
    delay(1000);

    if (ResetGame) // Sjekker om ResetGame er forandret; den kan bli forandret i Interrupt()
    {
      digitalWrite(Reset_LED, HIGH);
      delay(500);
      digitalWrite(Reset_LED, LOW);
      delay(500);
      return 0;
    }
  }

  if (System_Coor[Progression][1] == B10000010) // Hvis siste LED-i visningen over havner på (0, 0) slås alle LED av for å skille mellom visning og lyset man kan kontrollere selv
  {
    ResetLEDs();
    delay(500);
  }

  ShowCurrentLED();
  OK_button_pushed = false;

  while (GameRound < GameLength && Answerstreak < WinAnswerstreak) // Man kontrollerer hvilket lys som lyser ved å trykke på knappene fram til man velger et ved å trykke OK
  {
    while (!Continue)
    {
      right_button_value = digitalRead(right_button);
      left_button_value = digitalRead(left_button);
      up_button_value = digitalRead(up_button);
      down_button_value = digitalRead(down_button);
      OK_button_value = digitalRead(OK_button);

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (left_button_value == LOW && !left_button_pushed)
      {
        left_button_pushed = !left_button_pushed;
        current_x_cor -= 1;

        ShowCurrentLED();
      }

      if (left_button_value == HIGH && left_button_pushed)
      {
        left_button_pushed = !left_button_pushed;
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (right_button_value == LOW && !right_button_pushed)
      {
        right_button_pushed = !right_button_pushed;
        current_x_cor += 1;

        ShowCurrentLED();
      }

      if (right_button_value == HIGH && right_button_pushed)
      {
        right_button_pushed = !right_button_pushed;
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (up_button_value == LOW && !up_button_pushed)
      {
        up_button_pushed = !up_button_pushed;
        current_y_cor -= 1;

        ShowCurrentLED();
      }

      if (up_button_value == HIGH && up_button_pushed)
      {
        up_button_pushed = !up_button_pushed;
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (down_button_value == LOW && !down_button_pushed)
      {
        down_button_pushed = !down_button_pushed;
        current_y_cor += 1;

        ShowCurrentLED();
      }

      if (down_button_value == HIGH && down_button_pushed)
      {
        down_button_pushed = !down_button_pushed;
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (ResetGame)
      {
        digitalWrite(Reset_LED, HIGH);
        delay(500);
        digitalWrite(Reset_LED, LOW);
        delay(500);
        return 0;
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------

      if (OK_button_value == LOW && !OK_button_pushed)
      {
        OK_button_pushed = !OK_button_pushed;
        digitalWrite(OK_LED, HIGH);
      }

      if (OK_button_value == HIGH && OK_button_pushed)
      {
        OK_button_pushed = !OK_button_pushed;
        Continue = true;
        digitalWrite(OK_LED, LOW);
      }

      // -------------------------------------------------------------
      // -------------------------------------------------------------
      // -------------------------------------------------------------
    }
    Continue = false;

    if (current_x_bin == System_Coor[Progression][0] && current_y_bin == System_Coor[Progression][1]) // Sjekker om avgitt svar er riktig
    {
      CorrectAns();
      Progression++;
    }
    else
    {
      WrongAns();
    }

    GameRound++;
  }

  if (Answerstreak == WinAnswerstreak) // Sjekker om spilleren vant spillet
  {
    Victory();
  }
  else
  {
    Loss();
  }
  return 0;
}

//--------------------------------------------------
// FUNCTIONS

void Interrupt()
{
  if (millis() - TimeOfLastReset >= 1000)
  {
    ResetGame = true;
    TimeOfLastReset = millis();
    ResetLEDs();
  }
}

void CorrectAns()
{
  Answerstreak++;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(Correct_LED, HIGH);
    delay(500);
    digitalWrite(Correct_LED, LOW);
    delay(500);
  }
  // Når riktig LED velges
}

void WrongAns()
{
  Answerstreak = 0;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(Wrong_LED, HIGH);
    delay(500);
    digitalWrite(Wrong_LED, LOW);
  }
  // Når feil LED velges
}

void Victory()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(OK_LED, HIGH);
    delay(500);
    digitalWrite(OK_LED, LOW);
    digitalWrite(Correct_LED, HIGH);
    delay(500);
    digitalWrite(Correct_LED, LOW);
  }
}

void Loss()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(Reset_LED, HIGH);
    delay(500);
    digitalWrite(Reset_LED, LOW);
    digitalWrite(Wrong_LED, HIGH);
    delay(500);
    digitalWrite(Wrong_LED, LOW);
  }
}

void ShowSystemLED()
{
  digitalWrite(LatchPin, 0);
  shiftOut(DataPin, ClockPin, LSBFIRST, System_Coor[Progression][0]);
  shiftOut(DataPin, ClockPin, LSBFIRST, System_Coor[Progression][1]);
  digitalWrite(LatchPin, 1);
}

void ShowCurrentLED()
{
  ControlCoorLimits();
  Conversion_Coordinates(current_x_cor, current_y_cor);
  current_x_bin = ShiftOutByte1;
  current_y_bin = ShiftOutByte2;

  digitalWrite(LatchPin, 0);
  shiftOut(DataPin, ClockPin, LSBFIRST, current_x_bin);
  shiftOut(DataPin, ClockPin, LSBFIRST, current_y_bin);
  digitalWrite(LatchPin, 1);
}

void ResetLEDs()
{
  digitalWrite(LatchPin, 0);
  shiftOut(DataPin, ClockPin, LSBFIRST, B00000000);
  shiftOut(DataPin, ClockPin, LSBFIRST, B00000000);
  digitalWrite(LatchPin, 1);
}

// ----------------------------------------------
// KOORDINATER

void ControlCoorLimits() // Sørger for at man ikke kan bevege seg av brettet
{
  if (current_x_cor > 9)
  {
    current_x_cor -= 10;
  }

  if (current_y_cor > 4)
  {
    current_y_cor -= 5;
  }

  if (current_x_cor < 0)
  {
    current_x_cor += 10;
  }

  if (current_y_cor < 0)
  {
    current_y_cor += 5;
  }
}

void Conversion_Coordinates(int x, int y) // Gjør koordinater om til binære data som kan skiftes ut
{
  // Convert from coordinates to binary
  ShiftOutByte1 = B00000000;
  ShiftOutByte2 = B00000000;

  bitSet(ShiftOutByte2, (7 - y));

  if (x < 2)
  {
    bitSet(ShiftOutByte2, (1 - x));
  }
  else
  {
    bitSet(ShiftOutByte1, (9 - x)); // 7-(x-2)
  }
}

// -----------------------------------------------------------
// SYSTEM FUNKSJONER

void RegularJumpHorizontal()
{
  int i = 0;
  int jump = random(1, 8);
  int x_coor = random(0, 9);
  int y_coor = random(0, 4);

  do
  {
    Conversion_Coordinates(x_coor, y_coor);
    System_Coor[i][0] = ShiftOutByte1;
    System_Coor[i][1] = ShiftOutByte2;

    x_coor += jump;

    if (x_coor > 9)
    {
      x_coor -= 10;
      y_coor += 1;
    }

    if (y_coor > 4)
    {
      y_coor -= 5;
    }

    i++;

  } while (i < GameLength);
}

void RegularJumpVertical()
{
  int i = 0;
  int jump = random(1, 4);
  int x_coor = random(0, 4);
  int y_coor = random(0, 4);

  do
  {
    Conversion_Coordinates(x_coor, y_coor);
    System_Coor[i][0] = ShiftOutByte1;
    System_Coor[i][1] = ShiftOutByte2;

    y_coor += jump;

    if (y_coor > 4)
    {
      y_coor -= 5;
      x_coor += 1;
    }
    if (x_coor > 9)
    {
      x_coor -= 10;
    }

    i++;

  } while (i < GameLength);
}
