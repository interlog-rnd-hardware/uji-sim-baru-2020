void mobilstart()
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
// while (HC12.available()) {        // If HC-12 has data
  while(Serial1.available()) {
    //Serial.write(HC12.read());      // Send the data to Serial monitor
//    co = HC12.read();
    co = Serial1.read();
    s.concat(co);
   
  } 
  Serial.println(s);
  
 // int st = s.toInt();
  if (s == "1")
  {
    
  }
  if (s == "0")
  {
    
  }
}
    
