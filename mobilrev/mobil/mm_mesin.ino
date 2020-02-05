void mm_mesin()
{
  mmesin = digitalRead(msin);
  
  str_mesin=String(mmesin);
  str_mesin.toCharArray(cmesin,2);
}
