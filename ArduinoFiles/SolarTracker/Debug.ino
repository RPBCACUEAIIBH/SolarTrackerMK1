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
      else if (SRAvg < SLAvg + Threshold - Hysteresis || SLAvg < SRAvg + Threshold - Hysteresis)
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
      else if (STAvg < SBAvg + Threshold - Hysteresis || SBAvg < STAvg + Threshold - Hysteresis)
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
        LRTurn = " S ";
        UDTurn = " S ";
      }
      Serial.print (Sleeping);
      Sleepiness = true;
    }
    else
    {
      Serial.print (Active);
      Sleepiness = false;
    }
    Serial.print (";   ");
    Serial.print ("Sensor values: ");
    if (SLAvg < 100) Serial.print (" ");
    if (SLAvg < 10) Serial.print (" ");
    Serial.print (SLAvg);
    Serial.print ("(L) ");
    if (SRAvg < 100) Serial.print (" ");
    if (SRAvg < 10) Serial.print (" ");
    Serial.print (SRAvg);
    Serial.print ("(R) ");
    if (STAvg < 100) Serial.print (" ");
    if (STAvg < 10) Serial.print (" ");
    Serial.print (STAvg);
    Serial.print ("(T) ");
    if (SBAvg < 100) Serial.print (" ");
    if (SBAvg < 10) Serial.print (" ");
    Serial.print (SBAvg);
    Serial.print ("(B) ");
    Serial.print (">> ");
    Serial.print (LRTurn);
    Serial.print (" ");
    Serial.print (UDTurn);
    Serial.print (";   ");
    Serial.print ("Threshold: ");
    if (Threshold < 100) Serial.print (" ");
    if (Threshold < 10) Serial.print (" ");
    Serial.print (Threshold);
    Serial.print ("; ");
    Serial.print ("Speed: ");
    if (Speed < 100) Serial.print (" ");
    if (Speed < 10) Serial.print (" ");
    Serial.print (Speed);
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
