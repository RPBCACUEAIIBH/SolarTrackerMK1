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

  if (SHAvg > STAvg + Threshold)
  {
    switch (Cycle)
    {
      case 0: Active = "(~-~)";
      break;
      case 64: Active = "(~\\~)";
      break;
      case 128: Active = "(~|~)";
      break;
      case 192: Active = "(~/~)";
      break;
      case 256: Active = "(~-~)";
      break;
      case 320: Active = "(~\\~)";
      break;
      case 384: Active = "(~|~)";
      break;
      case 448: Active = "(~/~)";
      break;
    }
    PumpState = "On ";
  }
  else
  {
    switch (Cycle)
    {
      case 0: Active = "(~~~)";
      break;
      case 64: Active = "(~~~)";
      break;
      case 128: Active = "(~~~)";
      break;
      case 192: Active = "(~~~)";
      break;
      case 256: Active = "(~~~)";
      break;
      case 320: Active = "(~~~)";
      break;
      case 384: Active = "(~~~)";
      break;
      case 448: Active = "(~~~)";
      break;
    }
    PumpState = "Off";
  }
  
  Serial.print ("Tank Temp.: ");
  if (STAvg < 100) Serial.print ("0");
  if (STAvg < 10) Serial.print ("0");
  Serial.print (STAvg);
  Serial.print ("; ");
  Serial.print ("Max Temp.: ");
  if (ThermalLimit < 100) Serial.print ("0");
  if (ThermalLimit < 10) Serial.print ("0");
  Serial.print (ThermalLimit);
  Serial.print (" >> ");
  if (STAvg < ThermalLimit)
  {
    Serial.print (Active);
    Sleepiness = false;
  }
  else
  {
    Serial.print (Sleeping);
    Sleepiness = true;
  }
  Serial.print (";   ");
  Serial.print ("Head Temp.: ");
  if (SHAvg < 100) Serial.print (" ");
  if (SHAvg < 10) Serial.print (" ");
  Serial.print (SHAvg);
  Serial.print (" >> ");
  Serial.print (PumpState);
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
}
