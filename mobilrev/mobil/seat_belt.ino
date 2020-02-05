void seat_belt()
{
  sabuk = digitalRead(pinsabuk);
  str_sabuk=String(sabuk);
  str_sabuk.toCharArray(csabuk,2);
}
