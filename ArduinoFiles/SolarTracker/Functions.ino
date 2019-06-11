void ReadInterface ()
{
  if (SensitivityBoost == true && Boosted == true || SensitivityBoost == false)
  {
    TValues[Index] = analogRead (TP) / 4;
    NMValues[Index] = analogRead (NMP) / 4;
    SValues[Index] = analogRead (SPEEDP) / 4;
    
    Threshold = 0;
    NightMode = 0;
    Speed = 0;
    
    for (int i; i < Samples; i++)
    {
      Threshold = Threshold + TValues[i];
      NightMode = NightMode + NMValues[i];
      Speed = Speed + SValues[i];
    }
    Threshold /= Samples;
    if (Threshold <= 254 - Hysteresis)
    {
      Threshold = Threshold + Hysteresis;
    }
    if (Threshold < Hysteresis)
    {
      Threshold = Hysteresis;
    }
    NightMode /= Samples;
    if (Sleepiness == true && NightMode <= 255)
    {
      NightMode = NightMode + Hysteresis;
    }
    Speed /= Samples;
  }
  
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
  
  SLAvg = 0;
  SRAvg = 0;
  STAvg = 0;

  for (int i; i < Samples; i++)
  {
    SLAvg = SLAvg + SLValues[i];
    SRAvg = SRAvg + SRValues[i];
    STAvg = STAvg + STValues[i];
  }
  SLAvg /= Samples;
  SRAvg /= Samples;
  STAvg /= Samples;
  SBAvg = SLAvg + SRAvg;
  SBAvg /= 2;
  SAvg = SLAvg + SRAvg + STAvg;
  SAvg /= 3;
}

void Motion () // For driving transistors and/or relays.
{
  if (SensitivityBoost == true && SAvg >= NightMode && AutoPositioning == true && Boosted == true || SensitivityBoost == true && AutoPositioning == true && Boosted == false || SensitivityBoost == false && SAvg >= NightMode && AutoPositioning == true) // AutoMode
  {
    analogWrite (SPEED, Speed);
    // Overcast (Periodic search not yet implemented...)
    // Turn RIGHT
    if (SRAvg >= SLAvg + Threshold)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (RIGHT, HIGH);
      }
      else
      {
        digitalWrite (RIGHT, LOW);
      }
    }
    else if (SRAvg < SLAvg + Threshold - Hysteresis)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (RIGHT, LOW);
      }
      else
      {
        digitalWrite (RIGHT, HIGH);
      }
    }
    // Turn LEFT
    if (SLAvg >= SRAvg + Threshold)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, HIGH);
      }
      else
      {
        digitalWrite (LEFT, LOW);
      }
    }
    else if (SLAvg < SRAvg + Threshold - Hysteresis)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, LOW);
      }
      else
      {
        digitalWrite (LEFT, HIGH);
      }
    }
    // Turn UP
    if (STAvg >= SBAvg + Threshold)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (UP, HIGH);
      }
      else
      {
        digitalWrite (UP, LOW);
      }
    }
    else if (STAvg < SBAvg + Threshold - Hysteresis)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (UP, LOW);
      }
      else
      {
        digitalWrite (UP, HIGH);
      }
    }
    // Turn DOWN
    if (SBAvg >= STAvg + Threshold)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (DOWN, HIGH);
      }
      else
      {
        digitalWrite (DOWN, LOW);
      }
    }
    else if (SBAvg < STAvg + Threshold - Hysteresis)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (DOWN, LOW);
      }
      else
      {
        digitalWrite (DOWN, HIGH);
      }
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

    analogWrite (SPEED, Speed);
    // Turn RIGHT
    if (ManRight[0] == LOW && ManLeft[0] != LOW)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (RIGHT, HIGH);
      }
      else
      {
        digitalWrite (RIGHT, LOW);
      }
    }
    else
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (RIGHT, LOW);
      }
      else
      {
        digitalWrite (RIGHT, HIGH);
      }
    }
    // Turn LEFT
    if (ManLeft[0] == LOW && ManRight[0] != LOW)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, HIGH);
      }
      else
      {
        digitalWrite (LEFT, LOW);
      }
    }
    else
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, LOW);
      }
      else
      {
        digitalWrite (LEFT, HIGH);
      }
    }
    // Turn UP
    if (ManUp[0] == LOW && ManDown[0] != LOW)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (UP, HIGH);
      }
      else
      {
        digitalWrite (UP, LOW);
      }
    }
    else
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (UP, LOW);
      }
      else
      {
        digitalWrite (UP, HIGH);
      }
    }
    // Turn DOWN
    if (ManDown[0] == LOW && ManUp[0] != LOW)
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (DOWN, HIGH);
      }
      else
      {
        digitalWrite (DOWN, LOW);
      }
    }
    else
    {
      if (LowActiveRelays == false)
      {
        digitalWrite (DOWN, LOW);
      }
      else
      {
        digitalWrite (DOWN, HIGH);
      }
    }
  }
  else // Night Mode
  {
    if (Return == true && ReturnDir == 'L')
    {
      analogWrite (SPEED, Speed);
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, HIGH);
        digitalWrite (DOWN, HIGH);
        digitalWrite (UP, LOW);
        digitalWrite (RIGHT, LOW);
      }
      else
      {
        digitalWrite (LEFT, LOW);
        digitalWrite (DOWN, LOW);
        digitalWrite (UP, HIGH);
        digitalWrite (RIGHT, HIGH);
      }
      digitalWrite (SLEEP, HIGH);
      Sleepiness = true;
    }
    else if (Return == true)
    {
      analogWrite (SPEED, Speed);
      if (LowActiveRelays == false)
      {
        digitalWrite (LEFT, LOW);
        digitalWrite (DOWN, HIGH);
        digitalWrite (UP, LOW);
        digitalWrite (RIGHT, HIGH);
      }
      else
      {
        digitalWrite (LEFT, HIGH);
        digitalWrite (DOWN, LOW);
        digitalWrite (UP, HIGH);
        digitalWrite (RIGHT, LOW);
      }
      digitalWrite (SLEEP, HIGH);
      Sleepiness = true;
    }
    else
    {
      digitalWrite (SPEED, LOW);
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
      digitalWrite (SLEEP, HIGH);
      Sleepiness = true;
    }
  }
}

void Boost () // Sensitivity enhancement
{
  if (SensitivityBoost == true && SAvg <= 50 && Boosted == false) // 50 - Just below 1V
  {
    analogReference(INTERNAL);
    Boosted = true;
    // Flushing value hystory otherwise this may cause problems...
    for (int i; i < Samples; i++) // discard a few readings...
    {
      SLValues[i] = analogRead (SL) / 4;
      SRValues[i] = analogRead (SR) / 4;
      STValues[i] = analogRead (ST) / 4;
    }
    SLAvg = 0;
    SRAvg = 0;
    STAvg = 0;
    for (int i; i < Samples; i++)
    {
      SLAvg = SLAvg + SLValues[i];
      SRAvg = SRAvg + SRValues[i];
      STAvg = STAvg + STValues[i];
    }
    SLAvg /= Samples;
    SRAvg /= Samples;
    STAvg /= Samples;
    SBAvg = SLAvg + SRAvg;
    SBAvg /= 2;
  }
  else if (SensitivityBoost == true && SAvg >= 250 && Boosted == true) // - 245 - Just above 1.05V
  {
    analogReference(DEFAULT);
    Boosted = false;
    // Flushing value hystory otherwise this may cause problems...
    for (int i; i < Samples; i++) // discard a few readings...
    {
      SLValues[i] = analogRead (SL) / 4;
      SRValues[i] = analogRead (SR) / 4;
      STValues[i] = analogRead (ST) / 4;
    }
    SLAvg = 0;
    SRAvg = 0;
    STAvg = 0;
    for (int i; i < Samples; i++)
    {
      SLAvg = SLAvg + SLValues[i];
      SRAvg = SRAvg + SRValues[i];
      STAvg = STAvg + STValues[i];
    }
    SLAvg /= Samples;
    SRAvg /= Samples;
    STAvg /= Samples;
    SBAvg = SLAvg + SRAvg;
    SBAvg /= 2;
  }
}
