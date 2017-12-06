#define BUTTON_INPUT_PIN 6
#define LED_OUTPUT_PIN 3

#define DEAD_BUTTON_TIME 300

// ---------------------------------------------------
void readButtonValue();
void writeSerial();
void writeLed();

// ---------------------------------------------------
int buttonState;
int buttonPreviousState; // to activate function on release
bool isButtonDead; 
unsigned long nextTimeButtonIsAlive;
bool shouldSendFood;

// ---------------------------------------------------
// ---------------------------------------------------
void setup()
{
  Serial.begin(9600);
  
  pinMode(BUTTON_INPUT_PIN, INPUT);
  pinMode(LED_OUTPUT_PIN, OUTPUT);

  buttonState = LOW;
  buttonPreviousState = buttonState;
  isButtonDead = false;
  nextTimeButtonIsAlive = 0;
  shouldSendFood = false;
  
}

// ---------------------------------------------------
void loop()
{
  readButtonValue();

  writeSerial();
  writeLed();
  
  delay(50);
}

// ---------------------------------------------------
void readButtonValue()
{
  if (nextTimeButtonIsAlive < millis())
  { 
    isButtonDead = false;
    buttonState = digitalRead(BUTTON_INPUT_PIN);
  
    if (buttonPreviousState == LOW && buttonState == HIGH)
    {
      isButtonDead = true;
      nextTimeButtonIsAlive = millis() + DEAD_BUTTON_TIME;
      shouldSendFood = true;
    }
    
    buttonPreviousState = buttonState;
  }
}

// ---------------------------------------------------
void writeSerial()
{
  if (shouldSendFood)
  {
    Serial.print("1");
    //Serial.print(1);
    shouldSendFood = false;
  }  
}


void writeLed()
{
  if(!isButtonDead) // if button is active
  {
    digitalWrite(LED_OUTPUT_PIN, LOW); // led off
  }
  else
  {
    digitalWrite(LED_OUTPUT_PIN, HIGH);  // led on
  }
}


