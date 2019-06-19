// This is an expansion of the solar tracker, for controlling a pump in case of a hydro-thermic system.
// Couldn't fit all the tracking and pump control functionalities, and the user interface on 1 arduino, and none of us had megas to play with. We eventually agreed to put the tracking on 1 arduino, and the pump on the other since the pump is only necessary for a hydro-thermic system.
// Version 0.1

// Pins
int SPEED = 11; // Pump Speed (only for DC pump...)
int OHP = 12; //  Overheat Protection
int RELAY = 13; // Pump Relay
int SH = A0; // Head Sensor
int ST = A1; // Tank Sensor
int TP = A2; // Threshold Pot
int TLP = A3; // Thermal Limit Pot
int SPEEDP = A4; // Speed Pot (only for DC pump...)

// Constants
const byte Samples = 128; // Valid range: 1 - 128 (128 is the maximum number of 8 bit samples that can be averaged in an integer value... Higher sample size is more accurate, but less responsive... )
const boolean LowActiveRelays = false; // If your relays are activated when you pull the pin low, it should be set to true otherwise it should be set to false.
const byte Hysteresis = 1; // This(and averaging lots of samples) makes absolutely sure that the relays do not get destroyed by fast switching on and off.

// Variables
unsigned int SHAvg; // Averaged Head sensor value (Measured)
unsigned int STAvg; // Averaged Tank sensor value (Measured)
int Index = Samples - 1;
byte SHValues[128];
byte STValues[128];
unsigned int Threshold; // Won't turn if the difference between sensors is less then this valiue (Lower this value for more, raise for less accuracy, but for high accuracy the sensors may need to be matched...)
unsigned int ThermalLimit; // When the temperature in the tank reaches this limit, the overheat protection pin is set HIGH to signal the tracker to go to sleep.
unsigned int Speed; // Pump speed (only for DC pump...)
byte TValues[128];
byte TLValues[128];
byte SValues[128];
unsigned int Cycle = 0;
String Active;
String Sleeping;
String PumpState;
boolean DisplayString = false;
boolean Sleepiness = false;

// Functions
void ReadInterface (); // Logic
void ReadSensors (); // Logic
void Action (); // Logic
void DataStream (); // Debug

void setup()
{
  analogReference(DEFAULT);
  pinMode(SPEEDP, INPUT_PULLUP); // Debug
  pinMode(SPEED, OUTPUT);
  pinMode(OHP, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(SPEED, LOW);
  digitalWrite(OHP, LOW);
  if (LowActiveRelays == false)
    digitalWrite(RELAY, LOW);
  else
    digitalWrite(RELAY, HIGH);

  for (int i; i < 5; i++) // Discarding first few measurements since the reference voltage may be unstable...
  {
    SHValues[0] = analogRead (SH) / 4;
    STValues[0] = analogRead (ST) / 4;
    TValues[0] = analogRead (TP) / 4;
    TLValues[0] = analogRead (TLP) / 4;
    SValues[0] = analogRead (SPEEDP) / 4;
  }

  for (int i; i < Samples; i++)
  {
    SHValues[i] = analogRead (SH) / 4;
  }
  for (int i; i < Samples; i++)
  {
    STValues[i] = analogRead (ST) / 4;
  }
  for (int i; i < Samples; i++)
  {
    TValues[i] = analogRead (TP) / 4;
  }
  for (int i; i < Samples; i++)
  {
    TLValues[i] = analogRead (TLP) / 4;
  }
  for (int i; i < Samples; i++)
  {
    SValues[i] = analogRead (SPEEDP) / 4;
  }
  Serial.begin (115200);
}

void loop()
{
  Index += 1;
  Index %= Samples;
  ReadInterface ();
  ReadSensors ();
  Action ();
  DataStream ();
  Cycle += 1;
  Cycle %= 512;
  delay(1);
}
