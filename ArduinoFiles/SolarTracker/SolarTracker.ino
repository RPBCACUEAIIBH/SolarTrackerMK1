#include <EEPROM.h>

// Please note that this project was made for someone with an already existing system. Had to work with he already had rather then design everything from scratch!
// This is Version: 0.1

// Pins
int SL = A0; // Left sensor
int SR = A1; // Right sensor
int ST = A2; // Top sensor
int LEFT = 2;
int UP = 4;
int DOWN = 7;
int RIGHT = 8;
int SLEEP = 13;
// Pins Left unused: 3(pwm), 5(pwm), 6(pwm), 9(pwm), 10(pwm), 11(pwm), 12, A3, A4(I2C), A5(I2C), A6(ADC only), A7(ADC only)(Pins A6 and A7 May not be available on older arduinos.)
// Keep the pin configuration if you're planning on updating to the newest version later!

// Constants
byte Samples = 128; // Valid range: 1 - 128 (128 is the maximum number of 8 bit samples that can be averaged in an integer value... Higher sample size is more accurate, but less responsive... )
byte Threshold = 30; // Won't turn if the difference between sensors is less then this valiue (Lower this value for more, raise for less accuracy, but for high accuracy the sensors may need to be matched...)
byte NightMode = 75; // Bbelow this value the controller does not bother turning...

// Variables
int Index = Samples - 1;
unsigned int SLAvg; // Averaged Left sensor value (Measured)
unsigned int SRAvg; // Averaged Right sensor value (Measured)
unsigned int STAvg; // Averaged Top sensor value (Measured)
unsigned int SBAvg; // Averaged Bottom sensor value (Calculated)
unsigned int SAvg; // Overall brightness (Calculated)
byte SLValues[128];
byte SRValues[128];
byte STValues[128];

// Functions
void ReadSensors ();
void DirectDrive ();
void DataStream ();


void setup()
{
  pinMode (LEFT, OUTPUT);
  pinMode (DOWN, OUTPUT);
  pinMode (UP, OUTPUT);
  pinMode (RIGHT, OUTPUT);
  pinMode (SLEEP, OUTPUT);
  digitalWrite (LEFT, LOW);
  digitalWrite (DOWN, LOW);
  digitalWrite (UP, LOW);
  digitalWrite (RIGHT, LOW);

  for (int i; i < 5; i++) // Discarding first few measurements since the reference voltage may be unstable...
  {
    SLValues[0] = analogRead (SL) / 4;
    SRValues[0] = analogRead (SR) / 4;
    STValues[0] = analogRead (ST) / 4;
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
  Serial.begin (115200);
}

void loop()
{
  ReadSensors ();
  DirectDrive ();
  DataStream ();
}
