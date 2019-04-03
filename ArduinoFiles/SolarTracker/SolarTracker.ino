// Please note that this project was made for someone with an already existing system. Had to work with he already had rather then design everything from scratch!
// Made primarily for Arduino nano and pro mini.(The new versions of pro mini that has A6 and A7 available, but if PWM speed control is not required any older version will do as those pins only read motor speed settings from pots...)
// This is Version: 0.4.1 (not fully tested)

// Pins
int SL = A0; // Left sensor
int SR = A1; // Right sensor
int ST = A2; // Top sensor
int SB = A3; // Bottom sensor
int LEFT = 2; // Left trun relay signal
int UP = 4; // Up trun relay signal
int DOWN = 7; // Down trun relay signal
int RIGHT = 8; // Right trun relay signal
int SLEEP = 13; // Night mode indicator
int LRSPEED = 3; // Up-Down motor speed PWM output (Optional)
int UDSPEED = 5; // Up-Down motor speed PWM output (Optional)
int TP = A4; // Threshold pot
int NMP = A5; // NightMode pot
int LRSPEEDP = A6; // Left-Right motor speed pot (Optional, Required if PWM speed control is implemented.)
int UDSPEEDP = A7; // Up-Down motor speed pot (Optional, Required if PWM speed control is implemented.)
int MANLEFT = 9; // Left turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int MANUP = 10; // Up turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int AUTO = 6; // Toggle Automatic positioning (Optional, Required if either or both the Serial interface or other buttons are needed.)
int MANDOWN = 11; // Down turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int MANRIGHT = 12; // Right turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
// Use System monitor set to 115200 baud rate to read values!

// Constants
byte Samples = 128; // Valid range: 1 - 128 (128 is the maximum number of 8 bit samples that can be averaged in an integer value... Higher sample size is more accurate, but less responsive... )
boolean LowActiveRelays = true; // If your relays are activated when you pull the pin low, it should be set to true. (true is default cause it's made for someone using low active relays module...)

// Variables
boolean AutoPositioning = HIGH;
int Index = Samples - 1;
unsigned int SLAvg; // Averaged Left sensor value (Measured)
unsigned int SRAvg; // Averaged Right sensor value (Measured)
unsigned int STAvg; // Averaged Top sensor value (Measured)
unsigned int SBAvg; // Averaged Bottom sensor value (Measured)
unsigned int SAvg; // Overall brightness (Calculated)
byte SLValues[128];
byte SRValues[128];
byte STValues[128];
byte SBValues[128];
unsigned int Threshold; // Won't turn if the difference between sensors is less then this valiue (Lower this value for more, raise for less accuracy, but for high accuracy the sensors may need to be matched...)
unsigned int NightMode; // Bbelow this value the controller does not bother turning...
unsigned int LRSpeed; // Left-Right motor speed
unsigned int UDSpeed; // Up-Down motor speed
byte TValues[128];
byte NMValues[128];
byte LRSValues[128];
byte UDSValues[128];
boolean ManLeft[2] = {LOW, LOW};
boolean ManUp[2] = {LOW, LOW};
boolean Auto[2] = {LOW, LOW};
boolean ManDown[2] = {LOW, LOW};
boolean ManRight[2] = {LOW, LOW};
unsigned int Cycle = 0;
String Active;
String Sleeping;
String LRTurn;
String UDTurn;
boolean DisplayString = false;
byte Hysteresis = 4; // This(and averaging lots of samples) makes absolutely sure that the relays do not get destroyed by fast switching on and off.
boolean Sleepiness = false; // Sleep-Auto mode hysteresis...

// Functions
void ReadInterface (); // Logic
void ReadSensors (); // Logic
void Motion (); // Logic
void DataStream (); // Debug


void setup()
{
  pinMode (LEFT, OUTPUT);
  pinMode (DOWN, OUTPUT);
  pinMode (UP, OUTPUT);
  pinMode (RIGHT, OUTPUT);
  pinMode (SLEEP, OUTPUT);
  pinMode (LRSPEED, OUTPUT);
  pinMode (UDSPEED, OUTPUT);
  pinMode (MANLEFT, INPUT_PULLUP);
  pinMode (MANUP, INPUT_PULLUP);
  pinMode (AUTO, INPUT_PULLUP);
  pinMode (MANDOWN, INPUT_PULLUP);
  pinMode (MANRIGHT, INPUT_PULLUP);
  if (LowActiveRelays == false)
  {
    digitalWrite (LEFT, LOW);
    digitalWrite (DOWN, LOW);
    digitalWrite (UP, LOW);
    digitalWrite (RIGHT, LOW);
  }
  else
  {
    digitalWrite (LEFT, HIGH);
    digitalWrite (DOWN, HIGH);
    digitalWrite (UP, HIGH);
    digitalWrite (RIGHT, HIGH);
  }
  digitalWrite (SLEEP, LOW);
  digitalWrite (LRSPEED, LOW);
  digitalWrite (UDSPEED, LOW);

  for (int i; i < 5; i++) // Discarding first few measurements since the reference voltage may be unstable...
  {
    SLValues[0] = analogRead (SL) / 4;
    SRValues[0] = analogRead (SR) / 4;
    STValues[0] = analogRead (ST) / 4;
    SBValues[0] = analogRead (SB) / 4;
    TValues[0] = analogRead (TP) / 4;
    NMValues[0] = analogRead (NMP) / 4;
    LRSValues[0] = analogRead (LRSPEEDP) / 4;
    UDSValues[0] = analogRead (UDSPEEDP) / 4;
  }

  for (int i; i < Samples; i++)
  {
    SLValues[i] = analogRead (SL) / 4;
  }
  for (int i; i < Samples; i++)
  {
    SRValues[i] = analogRead (SR) / 4;
  }
  for (int i; i < Samples; i++)
  {
    STValues[i] = analogRead (ST) / 4;
  }
  for (int i; i < Samples; i++)
  {
    SBValues[i] = analogRead (SB) / 4;
  }
  for (int i; i < Samples; i++)
  {
    TValues[i] = analogRead (TP) / 4;
  }
  for (int i; i < Samples; i++)
  {
    NMValues[i] = analogRead (NMP) / 4;
  }
  for (int i; i < Samples; i++)
  {
    LRSValues[i] = analogRead (LRSPEEDP) / 4;
  }
  for (int i; i < Samples; i++)
  {
    UDSValues[i] = analogRead (UDSPEEDP) / 4;
  }
  Serial.begin (115200);
  Serial.println ("The display function slows down the execution, therefore it's only available in manual positioning mode. (Press the \"Auto\" button to toggle between Manual and Automatic mode.)");
}

void loop()
{
  Index += 1;
  Index %= Samples;
  ReadInterface ();
  ReadSensors ();
  Motion ();
  DataStream ();
  Cycle += 1;
  Cycle %= 512;
}
