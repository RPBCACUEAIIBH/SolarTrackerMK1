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
  NightMode /= Samples;
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

void DirectDrive () // For driving transistors and/or relays.
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
    else
    {
      digitalWrite (RIGHT, LOW);
    }
    // Turn LEFT
    if (SLAvg >= SRAvg + Threshold)
    {
      digitalWrite (LEFT, HIGH);
    }
    else
    {
      digitalWrite (LEFT, LOW);
    }
    // Turn UP
    if (STAvg >= SBAvg + Threshold)
    {
      digitalWrite (UP, HIGH);
    }
    else
    {
      digitalWrite (UP, LOW);
    }
    // Turn DOWN
    if (SBAvg >= STAvg + Threshold)
    {
      digitalWrite (DOWN, HIGH);
    }
    else
    {
      digitalWrite (DOWN, LOW);
    }
    digitalWrite (SLEEP, LOW);
  }
  else if (AutoPositioning == LOW) // ManualMode
  {
    if (Cycle < 256) // Blinking sleep indicator LED to indicate manual mode...
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
  }
}

void DataStream ()
{
  switch (Cycle)
  {
    case 0: Sleeping = "(Zzz)";
    break;
    case 64: Sleeping = "(ZZz)";
    break;
    case 128: Sleeping = "(ZZZ)";
    break;
    case 192: Sleeping = "(ZZz)";
    break;
    case 256: Sleeping = "(Zzz)";
    break;
    case 320: Sleeping = "(ZZz)";
    break;
    case 384: Sleeping = "(ZZZ)";
    break;
    case 448: Sleeping = "(ZZz)";
    break;
  }

  switch (Cycle)
  {
    case 0: Active = "(*  )";
    break;
    case 64: Active = "( * )";
    break;
    case 128: Active = "(  *)";
    break;
    case 192: Active = "( * )";
    break;
    case 256: Active = "(*  )";
    break;
    case 320: Active = "( * )";
    break;
    case 384: Active = "(  *)";
    break;
    case 448: Active = "( * )";
    break;
  }
  
  if (AutoPositioning == LOW)
  { 
    // Turn RIGHT Simulation
    if (ManLeft[0] == HIGH && ManUp[0] == HIGH && ManDown[0] == HIGH && ManRight[0] == HIGH)
    {
      if (SRAvg >= SLAvg + Threshold) // Turn RIGHT Simulation
      {
        LRTurn = " R ";
      }
      else if (SLAvg >= SRAvg + Threshold) // Turn LEFT Simulation
      {
        LRTurn = " L ";
      }
      else
      {
        LRTurn = " S ";
      }
      if (STAvg >= SBAvg + Threshold) // Turn UP Simulation
      {
        UDTurn = " U ";
      }
      else if (SBAvg >= STAvg + Threshold) // Turn DOWN Simulation
      {
        UDTurn = " D ";
      }
      else
      {
        UDTurn = " S ";
      }
    }
    else
    {
      if (ManRight[0] == LOW && ManLeft[0] != LOW) // Turn RIGHT
      {
        LRTurn = " MR";
      }
      else if (ManLeft[0] == LOW && ManRight[0] != LOW) // Turn LEFT
      {
        LRTurn = " ML";
      }
      else
      {
        LRTurn = " MS";
      }
      if (ManUp[0] == LOW && ManDown[0] != LOW) // Turn UP
      {
        UDTurn = " MU";
      }
      else if (ManDown[0] == LOW && ManUp[0] != LOW) // Turn DOWN
      {
        UDTurn = " MD";
      }
      else
      {
        UDTurn = " MS";
      }
    }
    
    Serial.print ("AP: Off");
    Serial.print (";   ");
    Serial.print ("Light: ");
    if (SAvg < 100) Serial.print ("0");
    if (SAvg < 10) Serial.print ("0");
    Serial.print (SAvg);
    Serial.print ("; ");
    Serial.print ("Min Light: ");
    if (NightMode < 100) Serial.print ("0");
    if (NightMode < 10) Serial.print ("0");
    Serial.print (NightMode);
    Serial.print (" >> ");
    if (SAvg < NightMode)
    {
      if (ManLeft[0] == HIGH && ManUp[0] == HIGH && ManDown[0] == HIGH && ManRight[0] == HIGH)
      {
        LRTurn = "n/a";
        UDTurn = "n/a";
      }
      Serial.print (Sleeping);
    }
    else
    {
      Serial.print (Active);
    }
    Serial.print (";   ");
    Serial.print ("Sensor values: ");
    if (SLAvg < 100) Serial.print ("0");
    if (SLAvg < 10) Serial.print ("0");
    Serial.print (SLAvg);
    Serial.print ("(L) ");
    if (SRAvg < 100) Serial.print ("0");
    if (SRAvg < 10) Serial.print ("0");
    Serial.print (SRAvg);
    Serial.print ("(R) ");
    if (STAvg < 100) Serial.print ("0");
    if (STAvg < 10) Serial.print ("0");
    Serial.print (STAvg);
    Serial.print ("(T) ");
    if (SBAvg < 100) Serial.print ("0");
    if (SBAvg < 10) Serial.print ("0");
    Serial.print (SBAvg);
    Serial.print ("(B) ");
    Serial.print (">> ");
    Serial.print (LRTurn);
    Serial.print (" ");
    Serial.print (UDTurn);
    Serial.print (";   ");
    Serial.print ("Threshold: ");
    if (Threshold < 100) Serial.print ("0");
    if (Threshold < 10) Serial.print ("0");
    Serial.print (Threshold);
    Serial.print ("; ");
    Serial.print ("LRSpeed: ");
    if (LRSpeed < 100) Serial.print ("0");
    if (LRSpeed < 10) Serial.print ("0");
    Serial.print (LRSpeed);
    Serial.print ("; ");
    Serial.print ("UDSpeed: ");
    if (UDSpeed < 100) Serial.print ("0");
    if (UDSpeed < 10) Serial.print ("0");
    Serial.print (UDSpeed);
    Serial.println ("");
    DisplayString = true;
  }
  else
  {
    if (DisplayString == true)
    {
      Serial.println ("AP: On");
    }
    DisplayString = false;
  }
}
