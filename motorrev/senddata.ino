void senddata()
{
  kirim = "<" + nama + 
          mtr + "~" + 
          crfid/*"471847"*/ + "~" + 
          ctolehr/*"0"*/ + "~" + 
          ctolehl/*"0"*/ + "~" + 
          cpdr + "," + 
          cpdl + "," + 
          cstr + "," + 
          cstl + "~" + 
          cleh + "~" +
          ctegaki+ "~" + 
          ctegaki1 + ">"; // + "\r\n";
  kirim.toCharArray(ckirim,43);
  delay(50);
  HC12.write(ckirim);
  Serial.println(ckirim);
  
}
