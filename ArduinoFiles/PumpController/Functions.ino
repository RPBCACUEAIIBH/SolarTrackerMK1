void ReadInterface ()
{
  TValues[Index] = analogRead (TP) / 4;
  TLValues[Index] = analogRead (TLP) / 4;
  SValues[Index] = analogRead (SPEEDP) / 4;
  
  Threshold = 0;
  ThermalLimit = 0;
  Speed = 0;
  
  for (int i; i < Samples; i++)
  {
    Threshold = Threshold + TValues[i];
    ThermalLimit = ThermalLimit + TLValues[i];
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
  ThermalLimit /= Samples;
  if (Sleepiness == true && ThermalLimit >= Hysteresis) // ThermalLimit is the inverse of the NightMode of the tracker...
  {
    ThermalLimit = ThermalLimit - Hysteresis;
  }
  if (ThermalLimit < 2 * Threshold)
  {
    ThermalLimit = 2 * Threshold;
  }
  Speed /= Samples;
}

void ReadSensors ()
{
  SHValues[Index] = analogRead (SH) / 4;
  STValues[Index] = analogRead (ST) / 4;
  
  SHAvg = 0;
  STAvg = 0;

  for (int i; i < Samples; i++)
  {
    SHAvg = SHAvg + SHValues[i];
    STAvg = STAvg + STValues[i];
  }
  SHAvg /= Samples;
  STAvg /= Samples;
}

void Action ()
{
  // Relay and speed switching
  if (SHAvg >= STAvg + Threshold)
  {
    if (LowActiveRelays == false)
      digitalWrite(RELAY, HIGH);
    else
      digitalWrite(RELAY, LOW);
    analogWrite(SPEED, Speed);
  }
  else if (SHAvg < STAvg + Threshold - Hysteresis)
  {
    digitalWrite(SPEED, LOW);
    if (LowActiveRelays == false)
      digitalWrite(RELAY, LOW);
    else
      digitalWrite(RELAY, HIGH);
  }
  
  // Overheat Protection
  if (STAvg < ThermalLimit - Threshold && SHAvg < ThermalLimit)
  {
    digitalWrite(OHP, LOW);
    Sleepiness = false;
  }
  else
  {
    digitalWrite(OHP, HIGH);
    Sleepiness = true;
  }
}
