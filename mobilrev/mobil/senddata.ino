void senddata()
{
  kirim =                    "<" + 
          kirimnama        + "~" + 
          crfid/*"471847"*/+ "~" + 
          str_sabuk/*"0"*/  + "~" + 
          rfidtrek/*"0"*/  + "~" + 
          str_mesin            + "~" + //mesin
          encoder          + "~" +
          ctegaki          + "~" + 
          ctegaki1         + ">"; // + "\r\n";
  kirim.toCharArray(ckirim,43);
  delay(50);
//  HC12.write(ckirim);
  Serial1.write(ckirim);
  Serial.println(ckirim);
  
}
