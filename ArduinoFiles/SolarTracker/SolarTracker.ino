// Please note that this project was made for someone with an already existing system. Had to work with he already had rather then design everything from scratch!
// Made primarily for Arduino nano and pro mini.(The new versions of pro mini that has A6 and A7 available, but if PWM speed control is not required any older version will do as those pins only read motor speed settings from pots...)
// This is Version: 0.5.1 (not fully tested)

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
boolean LowActiveRelays = true; // If your relays are activated when you pull the pin low, it should be set to true otherwise it should be set to false.
byte Hysteresis = 1; // This(and averaging lots of samples) makes absolutely sure that the relays do not get destroyed by fast switching on and off.
const boolean SensitivityBoost = true; // Sensitivity boost on/off (Advanced feature, this may require adjusting threshold, and night mode, and potmeters are only adjustable in low light conditions, but may improve low light tracking by switching between VCC and internal 1.1V reference.)
const byte DefaultT = 10; // Default Threshold (Only relevant if Sensitivity boost is enabled!)
const byte DefaultNM = 100; // Default NightMode (Only relevant if Sensitivity boost is enabled!)
const byte DefaultLRS = 225; // Default Left-Right Speed (Only relevant if Sensitivity boost is enabled!)
const byte DefaultUDS = 225; // Default Up-Down Speed (Only relevant if Sensitivity boost is enabled!)
const boolean Return = false; // Returns to end position. (Inactive by default! This feature relies on the limit switches to stop the relays! If the switches are non-existent/broken, this may cause erratic behavior, and/or burn something!)
const char ReturnDir = 'L'; // Which way to turn L/R when going to sleep.

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
boolean Sleepiness = false; // Sleep-Auto mode hysteresis...
boolean Boosted = false; // Sensitivity boost... (false = aref set to VCC, true = aref set to internal 1.1v)

// Functions
void ReadInterface (); // Logic
void ReadSensors (); // Logic
void Motion (); // Logic
void DataStream (); // Debug
void Boost (); // Enhancement


void setup()
{
  delay (200);
  analogReference(DEFAULT);
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
  if (SensitivityBoost == false) // If Sensitivity boost is enabled, default values are used, since the the potsmeters can only be properly read when sensitivity is boosted(in low light).
  {
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
  }
  else
  {
    for (int i; i < Samples; i++)
    {
      TValues[i] = DefaultT;
    }
    for (int i; i < Samples; i++)
    {
      NMValues[i] = DefaultNM;
    }
    for (int i; i < Samples; i++)
    {
      LRSValues[i] = DefaultLRS;
      UDSValues[i] = DefaultUDS;
    }
  }
  Serial.begin (115200);
  Serial.println ("The display function slows down the execution, therefore it's only available in manual positioning mode. (Press the \"Auto\" button to toggle between Manual and Automatic mode.)");
  if (SensitivityBoost == true) Serial.println ("!!! WARNING !!! Since sensitivity boost is enabled, potmeters are only adjustable in low light conditions! If that's a problem, then disable it and re-upload!");
}

void loop()
{
  Index += 1;
  Index %= Samples;
  Boost ();
  ReadInterface ();
  ReadSensors ();
  Motion ();
  DataStream ();
  Cycle += 1;
  Cycle %= 512;
}
