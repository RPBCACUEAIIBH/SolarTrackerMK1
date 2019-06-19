// This is slightly faster 3 sensor version, optimized for older arduino pro mini on which A6 and A7 isn't available, and for using least amount of parts which is more cost efficient for mass production...
// This is Version: 0.3.2 (not fully tested)

// Pins
int SL = A0; // Left sensor
int SR = A1; // Right sensor
int ST = A2; // Top sensor
int LEFT = 2; // Left trun relay signal
int UP = 4; // Up trun relay signal
int DOWN = 7; // Down trun relay signal
int RIGHT = 8; // Right trun relay signal
int SLEEP = 13; // Night mode indicator
int SPEED = 3; // Motor speed PWM output (Optional, PWM speed control may extend relay life by interruption of ark while the relays are switching in case of DC motors.)
int TP = A4; // Threshold pot
int NMP = A5; // NightMode pot
int SPEEDP = A3; // Left-Right motor speed pot (Optional, only required if PWM speed control is implemented.)
int MANLEFT = 9; // Left turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int MANUP = 10; // Up turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int AUTO = 6; // Toggle Automatic positioning (Optional, Required if either or both the Serial interface or other buttons are needed.)
int MANDOWN = 11; // Down turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
int MANRIGHT = 12; // Right turn button for manual positioning (Optional, but highly recommended! Pressing it will switch to manual mode...)
// Pins Left unused: 5(PWM), A6(Analog only, unavailable on old arduino pro mini), A7(Analog only, unavailable on old arduino pro mini)
// Use System monitor set to 115200 baud rate to read values!

// Constants
const byte Samples = 128; // Valid range: 1 - 128 (128 is the maximum number of 8 bit samples that can be averaged in an integer value... Higher sample size is more accurate, but less responsive... )
const boolean LowActiveRelays = false; // If your relays are activated when you pull the pin low, it should be set to true otherwise it should be set to false.
const byte Hysteresis = 1; // This(and averaging lots of samples) makes absolutely sure that the relays do not get destroyed by fast switching on and off.
const boolean SensitivityBoost = true; // Sensitivity boost on/off (Advanced feature, this may require adjusting threshold, and night mode, and potmeters are only adjustable in low light conditions, but may improve low light tracking by switching between VCC and internal 1.1V reference.)
const byte DefaultT = 10; // Default Threshold (Only relevant if Sensitivity boost is enabled!)
const byte DefaultNM = 100; // Default NightMode (Only relevant if Sensitivity boost is enabled!)
const byte DefaultS = 225; // Default Speed (Only relevant if Sensitivity boost is enabled!)
const boolean Return = true; // Returns to end position. (Active by default! Prevents meltdown that I didn't think of before with the newly added pump controller measuring temperatures...)
const char ReturnDir = 'L'; // Which way to turn L/R when going to sleep.

// Variables
boolean AutoPositioning = HIGH;
int Index = Samples - 1;
unsigned int SLAvg; // Averaged Left sensor value (Measured)
unsigned int SRAvg; // Averaged Right sensor value (Measured)
unsigned int STAvg; // Averaged Top sensor value (Measured)
unsigned int SBAvg; // Averaged Bottom sensor value (Calculated)
unsigned int SAvg; // Overall brightness (Calculated)
byte SLValues[128];
byte SRValues[128];
byte STValues[128];
unsigned int Threshold; // Won't turn if the difference between sensors is less then this valiue (Lower this value for more, raise for less accuracy, but for high accuracy the sensors may need to be matched...)
unsigned int NightMode; // Bbelow this value the controller does not bother turning...
unsigned int Speed; // Motor speed
byte TValues[128];
byte NMValues[128];
byte SValues[128];
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
  analogReference(DEFAULT);
  pinMode (LEFT, OUTPUT);
  pinMode (DOWN, OUTPUT);
  pinMode (UP, OUTPUT);
  pinMode (RIGHT, OUTPUT);
  pinMode (SLEEP, OUTPUT);
  pinMode (SPEED, OUTPUT);
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
  digitalWrite (SPEED, LOW);

  for (int i; i < 5; i++) // Discarding first few measurements since the reference voltage may be unstable...
  {
    SLValues[0] = analogRead (SL) / 4;
    SRValues[0] = analogRead (SR) / 4;
    STValues[0] = analogRead (ST) / 4;
    TValues[0] = analogRead (TP) / 4;
    NMValues[0] = analogRead (NMP) / 4;
    SValues[0] = analogRead (SPEEDP) / 4;
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
      SValues[i] = analogRead (SPEEDP) / 4;
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
      SValues[i] = DefaultS;
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
