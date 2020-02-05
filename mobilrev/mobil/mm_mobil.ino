void mm_mobil()
{
  if ((counter>oldcounter) && (selisih == 1 || selisih == -1 || selisih2 == 1 || selisih2 == -1))
{
  maju++;
}
else if ((counter<oldcounter) && (selisih == 1 || selisih == -1 || selisih2 == 1 || selisih2 == -1))
{
  mundur++;
}
else if(selisih == 0 || selisih2 == 0)
{
  if (counter != oldcounter)
  {
    oldcounter = counter;
    maju=0;
    mundur=0;
  }
}
if(maju>1)
{
//  Serial.println("maju");
  majumundur = 1;
}
else if(mundur>1)
{
//  Serial.println("mundur");
  majumundur = 2;
}
else if(maju == 0 && mundur == 0)
{
//  Serial.println("stop");
  majumundur = 0;
}
encoder = (String)majumundur;
selisih = 0;
selisih2 = 0;
delay(50);

}

void ai0()
{
    selisih = counter-oldcounter;
  selisih2 = oldcounter - counter;
  oldcounter = counter;
  
  if(digitalRead(3)==LOW)
  {
    counter++;
  }
  else
  {
    counter--;
  }  
//  delay(50);
}

void ai1()
{
  selisih = counter-oldcounter;
  selisih2 = oldcounter - counter;
  oldcounter = counter;

  if(digitalRead(2)==LOW)
  {
    counter--;
  }
  else
  {
    counter++;
  }
//  delay(50);
}
