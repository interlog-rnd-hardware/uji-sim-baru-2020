void motorstart()
{
  
 // int ii;
// while (HC12.available()) // If HC-12 has data
// {        
//    
// // s = HC12.readString();
// // ii = HC12.parseInt();
//  co = HC12.read();
//  s += co;
// }
//   co=HC12.read();
//   delay(50);
//   Serial.println(s);
//   s = "";
//   start = s.toInt();
//   
//   if (start == 1) //reset kalo motor detect finish
//  {
//    delay(100);
//    start = 0;
//    }
//    else if (start != 1)
//  {
//     bacasensor = true;
//   }
 while (HC12.available()) {        // If HC-12 has data

    //Serial.write(HC12.read());      // Send the data to Serial monitor
    co = HC12.read();
    s.concat(co);
   
  } 
  Serial.println(s);
  
 // int st = s.toInt();
  if (s == "1")
  {
    s.toCharArray(cleh, 2);
    buz++;
    if(buz == 1)
    {
    bacasensor = true;
    buzzer_tone(1);
    delay(50);
    buzzer_tone(0);
    delay(50);
    buzzer_tone(1);
    delay(50);
    buzzer_tone(0);
    }
    detecttrack = 1;
    delay(3000);
    digitalWrite(right,LOW);
    digitalWrite(left,HIGH);
    delay(3000);
    digitalWrite(right,HIGH);
    digitalWrite(left,LOW);
  }
  if (s == "0")
  {
    s.toCharArray(cleh, 2);
    bacasensor = false;
    buz = 0;
    tolkanan = 0;
    tolehr = 0;
    tolehl = 0;
    detecttrack = 0;
  }
}
    
