const int left_button = 4;
const int right_button = 5;
const int up_button = 6;
const int down_button = 7;
const int reset_button = 2;
const int OK_button = 3;

int current_x_cor = 0;
int current_y_cor = 0;

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

bool Continue = false;
volatile bool ResetGame = false;

void setup()
{
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(OK_button, INPUT_PULLUP);
  pinMode(reset_button, INPUT_PULLUP);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(reset_button), Interrupt, FALLING);
}

void loop()
{
  // while(gameprogression < gamelength && !Victory) {
  while (Continue == false && ResetGame == false)
  {
    right_button_value = digitalRead(right_button);
    left_button_value = digitalRead(left_button);
    up_button_value = digitalRead(up_button);
    down_button_value = digitalRead(down_button);
    OK_button_value = digitalRead(OK_button);

    // ---------------------------------------------
    if (left_button_value == LOW && !left_button_pushed)
    {
      left_button_pushed = !left_button_pushed;
      Serial.println("left_button");
      // Something
    }
    if (left_button_value == HIGH && left_button_pushed)
    {
      left_button_pushed = !left_button_pushed;
    }

    // ---------------------------------------------
    if (right_button_value == LOW && !right_button_pushed)
    {
      right_button_pushed = !right_button_pushed;
      Serial.println("right_button");
      // Something
    }
    if (right_button_value == HIGH && right_button_pushed)
    {
      right_button_pushed = !right_button_pushed;
    }

    // ---------------------------------------------
    if (up_button_value == LOW && !up_button_pushed)
    {
      up_button_pushed = !up_button_pushed;
      Serial.println("up_button");
      // Something
    }
    if (up_button_value == HIGH && up_button_pushed)
    {
      up_button_pushed = !up_button_pushed;
    }

    // ---------------------------------------------
    if (down_button_value == LOW && !down_button_pushed)
    {
      down_button_pushed = !down_button_pushed;
      Serial.println("down_button");
      // Something
    }
    if (down_button_value == HIGH && down_button_pushed)
    {
      down_button_pushed = !down_button_pushed;
    }

    // ---------------------------------------------
    if (OK_button_value == LOW && !OK_button_pushed)
    {
      OK_button_pushed = !OK_button_pushed;
      Serial.println("OK_button");
      digitalWrite(7, HIGH);
      Continue = true;
    }
    if (OK_button_value == HIGH && OK_button_pushed)
    {
      OK_button_pushed = !OK_button_pushed;
    }
  }
  Serial.println("Outside");
  Continue = false;
  ResetGame = false;
}

void Interrupt()
{
  ResetGame = true;
}
