void ReadInterface ()
{
  TValues[Index] = analogRead (TP) / 4;
  NMValues[Index] = analogRead (NMP) / 4;
  LRSValues[Index] = analogRead (LRSPEEDP) / 4;
  UDSValues[Index] = analogRead (UDSPEEDP) / 4;
  
  Threshold = 0;
  NightMode = 0;
  LRSpeed = 0;
  UDSpeed = 0;
  
  for (int i; i < Samples; i++)
  {
    Threshold = Threshold + TValues[i];
    NightMode = NightMode + NMValues[i];
    LRSpeed = LRSpeed + LRSValues[i];
    UDSpeed = UDSpeed + UDSValues[i];
  }
  Threshold /= Samples;
  if (Threshold <= 254 - Hysteresis)
  {
    Threshold = Threshold + Hysteresis + 1;
  }
  if (Threshold < Hysteresis * 3)
  {
    Threshold = Hysteresis * 3;
  }
  NightMode /= Samples;
  if (Sleepiness == true && NightMode <= 255)
  {
    NightMode = NightMode + Hysteresis;
  }
  LRSpeed /= Samples;
  UDSpeed /= Samples;
  
  ManLeft[1] = ManLeft[0];
  ManLeft[0] = digitalRead (MANLEFT);
  ManUp[1] = ManUp[0];
  ManUp[0] = digitalRead (MANUP);
  Auto[1] = Auto[0];
  Auto[0] = digitalRead (AUTO);
  ManDown[1] = ManDown[0];
  ManDown[0] = digitalRead (MANDOWN);
  ManRight[1] = ManRight[0];
  ManRight[0] = digitalRead (MANRIGHT);

  if (ManLeft[0] != ManLeft[1] || ManUp[0] != ManUp[1] || Auto[0] != Auto[1] || ManDown[0] != ManDown[1] || ManRight[0] != ManRight[1]) // Debouncing buttons
  {
    delay (5);
    ManLeft[0] = digitalRead (MANLEFT);
    ManUp[0] = digitalRead (MANUP);
    Auto[0] = digitalRead (AUTO);
    ManDown[0] = digitalRead (MANDOWN);
    ManRight[0] = digitalRead (MANRIGHT);
  }

  if (ManLeft[0] == LOW || ManUp[0] == LOW || ManDown[0] == LOW || ManRight[0] == LOW) // You can't be in manual and automatic mode at the same time, it could potentially burn something...
  {
    AutoPositioning = LOW;
    Auto[0] = HIGH;
  }
  if (Auto[0] == LOW && Auto[1] == HIGH && AutoPositioning == LOW) AutoPositioning = HIGH;
  else if (Auto[0] == LOW && Auto[1] == HIGH && AutoPositioning == HIGH) AutoPositioning = LOW;
}

void ReadSensors ()
{
  SLValues[Index] = analogRead (SL) / 4;
  SRValues[Index] = analogRead (SR) / 4;
  STValues[Index] = analogRead (ST) / 4;
  SBValues[Index] = analogRead (SB) / 4;
  
  SLAvg = 0;
  SRAvg = 0;
  STAvg = 0;
  SBAvg = 0;

  for (int i; i < Samples; i++)
  {
    SLAvg = SLAvg + SLValues[i];
    SRAvg = SRAvg + SRValues[i];
    STAvg = STAvg + STValues[i];
    SBAvg = SBAvg + SBValues[i];
  }
  SLAvg /= Samples;
  SRAvg /= Samples;
  STAvg /= Samples;
  SBAvg /= Samples;
  SAvg = SLAvg + SRAvg + STAvg + SBAvg;
  SAvg /= 4;
}

void Motion () // For driving transistors and/or relays.
{
  if (SAvg >= NightMode && AutoPositioning == HIGH) // AutoMode
  {
    analogWrite (LRSPEED, LRSpeed);
    analogWrite (UDSPEED, UDSpeed);
    // Overcast (Periodic search not yet implemented...)
    // Turn RIGHT
    if (SRAvg >= SLAvg + Threshold)
    {
      digitalWrite (RIGHT, HIGH);
    }
    else if (SRAvg < SLAvg + Threshold - Hysteresis)
    {
      digitalWrite (RIGHT, LOW);
    }
    // Turn LEFT
    if (SLAvg >= SRAvg + Threshold)
    {
      digitalWrite (LEFT, HIGH);
    }
    else if (SLAvg < SRAvg + Threshold - Hysteresis)
    {
      digitalWrite (LEFT, LOW);
    }
    // Turn UP
    if (STAvg >= SBAvg + Threshold)
    {
      digitalWrite (UP, HIGH);
    }
    else if (STAvg < SBAvg + Threshold - Hysteresis)
    {
      digitalWrite (UP, LOW);
    }
    // Turn DOWN
    if (SBAvg >= STAvg + Threshold)
    {
      digitalWrite (DOWN, HIGH);
    }
    else if (SBAvg < STAvg + Threshold - Hysteresis)
    {
      digitalWrite (DOWN, LOW);
    }
    digitalWrite (SLEEP, LOW);
    Sleepiness = false;
  }
  else if (AutoPositioning == LOW) // ManualMode
  {
    if (Cycle % 64 < 32 ) // Blinking sleep indicator LED to indicate manual mode...
    {
      digitalWrite (SLEEP, HIGH);
    }
    else
    {
      digitalWrite (SLEEP, LOW);
    }

    analogWrite (LRSPEED, LRSpeed);
    analogWrite (UDSPEED, UDSpeed);
    // Turn RIGHT
    if (ManRight[0] == LOW && ManLeft[0] != LOW)
    {
      digitalWrite (RIGHT, HIGH);
    }
    else
    {
      digitalWrite (RIGHT, LOW);
    }
    // Turn LEFT
    if (ManLeft[0] == LOW && ManRight[0] != LOW)
    {
      digitalWrite (LEFT, HIGH);
    }
    else
    {
      digitalWrite (LEFT, LOW);
    }
    // Turn UP
    if (ManUp[0] == LOW && ManDown[0] != LOW)
    {
      digitalWrite (UP, HIGH);
    }
    else
    {
      digitalWrite (UP, LOW);
    }
    // Turn DOWN
    if (ManDown[0] == LOW && ManUp[0] != LOW)
    {
      digitalWrite (DOWN, HIGH);
    }
    else
    {
      digitalWrite (DOWN, LOW);
    }
  }
  else // Night Mode
  {
    digitalWrite (LRSPEED, LOW);
    digitalWrite (UDSPEED, LOW);
    digitalWrite (LEFT, LOW);
    digitalWrite (DOWN, LOW);
    digitalWrite (UP, LOW);
    digitalWrite (RIGHT, LOW);
    digitalWrite (SLEEP, HIGH);
    Sleepiness = true;
  }
}
