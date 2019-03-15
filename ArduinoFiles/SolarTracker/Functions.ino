void ReadSensors ()
{
  Index += 1;
  Index %= Samples;
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
  if (SAvg >= NightMode)
  {
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
  else
  {
    digitalWrite (LEFT, LOW);
    digitalWrite (DOWN, LOW);
    digitalWrite (UP, LOW);
    digitalWrite (RIGHT, LOW);
    digitalWrite (SLEEP, HIGH);
  }
}

void DataStream ()
{
  Serial.print ("SAvg: ");
  Serial.print (SAvg);
  Serial.print (" ");
  Serial.print ("SLAvg: ");
  Serial.print (SLAvg);
  Serial.print (" ");
  Serial.print ("SRAvg: ");
  Serial.print (SRAvg);
  Serial.print (" ");
  Serial.print ("SBAvg: ");
  Serial.print (SBAvg);
  Serial.print (" ");
  Serial.print ("STAvg: ");
  Serial.println (STAvg);
}
