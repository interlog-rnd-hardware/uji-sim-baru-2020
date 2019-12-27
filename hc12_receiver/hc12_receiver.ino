#include <SoftwareSerial.h>
SoftwareSerial HC12(11, 10); // HC-12 TX Pin, HC-12 RX Pin
String respon,respon1,respon2,respon3,respon4,respon5,finish,belok,s,sub;
int panjang,panjang1,panjang2,panjang3,panjang4,panjang5;
bool m1,m2,m3,m4,mm1,mm2,mm3,mm4,m5,rc,bkanan,bkiri;
char cc[2];
void setup() 
{
  m3 = false;
  rc = true;
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
}
void loop() 
{
  if (rc == true)
  {
    fromserver();
  }
  if (m3 == true)
  {
    ch12(); //motor 3
   
  }
}
void ch12()
{
  String dase;
  delay(200);
  while (HC12.available())  // If HC-12 has data
  {      
    char c2 = HC12.read();
    respon2.concat(c2);
  }
  Serial.println(respon2);
  panjang2 = respon2.length();
  String data2 = respon2.substring(0,34);
  String data3 = respon2.substring(13,47);
  int panjangdata2 = data2.length();
  int panjangdata3 = data3.length();
  //Serial.println("masuk ko");
  if (respon2.startsWith("<m_1") && respon.endsWith(">"))
//  {
    Serial.println(data2);
//  }//  if(panjang2 == 63 && respon2.startsWith("Motor"))
  
  rc = true;
  m3 = false;
  respon2="";
}

void fromserver()
{
  
  if (Serial.available()>0)
  {
    s = Serial.readString();
  }
  finish = s.substring(0,1);
  finish.toCharArray(cc,2);
  
  HC12.write(cc);
  delay(200);
  belok = s.substring(1,2);
  
  rc = false;
  m3 = true;
}
