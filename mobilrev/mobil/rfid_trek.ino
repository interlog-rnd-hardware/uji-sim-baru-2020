void rfid_trek()
{
//  while(UHF.available())
    while(Serial3.available())
  {
//    ctagg = UHF.read();
    ctagg = Serial3.read();
    //  Serial.print(c,HEX);
    //  Serial.print(" ");
    st += ctagg,HEX;
    st += " ";
  }
//  Serial.println(st);
  no1 = getValue(st,' ',3);
  no2 = getValue(st,' ',2);
  notag= no1.toInt();
  notag2 = no2.toInt();

    if(notag>=255 && notag<=237)
  {
    count = 0;
  }
  else if(notag>=205 && notag<=223)
  {
    count= 1;
  }
  else if(notag>=173 && notag<=191)
  {
    count = 2;
  }
  else if(notag>=141 && notag<=159)
  {
    count = 3;
  }
  else if(notag>=109 && notag<=127)
  {
    count = 4;
  }
  else if(notag>=77 && notag<=95)
  {
    count = 5;
  }
  else if(notag>=45 && notag<=63)
  {
    count = 6;
  }
  else if(notag>=13 && notag<=31)
  {
    count = 7;
  }
  else
  {
    count = 0;
  }


  if(notag2>=255 && notag2<=237)
  {
    count2 = 0;
  }
  else if(notag2>=205 && notag2<=223)
  {
    count2= 1;
  }
  else if(notag2>=173 && notag2<=191)
  {
    count2 = 2;
  }
  else if(notag2>=141 && notag2<=159)
  {
    count2 = 3;
  }
  else if(notag2>=109 && notag2<=127)
  {
    count2 = 4;
  }
  else if(notag2>=77 && notag2<=95)
  {
    count2 = 5;
  }
  else if(notag2>=45 && notag2<=63)
  {
    count2 = 6;
  }
  else if(notag2>=13 && notag2<=31)
  {
    count2 = 7;
  }
  else
  {
    count2 = 0;
  }
  
  realtag1 = ((255-notag)/2)-(6*count);
  realtag2 = ((255-notag2)/2)-(6*count2)+80;
//delay(100);
  if (realtag1 == 127 || realtag2 == 207)
  {
    tagtrack = 0;
//Serial.println("-");
  }
  else if (realtag2 == 80)
  {
//Serial.println(realtag1);
tagtrack=realtag1;
  }
  else if (realtag1 == 0)
  {
//Serial.println(realtag2);
tagtrack=realtag2;
  }
  else
  {
//Serial.println("-");
tagtrack=0;
  }
//  Serial.println(tagtrack);
  rfidtrek = (String)tagtrack;
//  if (tagtrack == 3)
//  {
//    kanan = "0";
//    kiri = "0";
//  }
}
