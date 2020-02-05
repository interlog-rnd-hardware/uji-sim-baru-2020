#include <SPI.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

#define RST_PIN 5
//SoftwareSerial HC12(13, 12); // HC-12 TX Pin, HC-12 RX Pin
//SoftwareSerial mp3module(10, 11);
//SoftwareSerial UHF(14, 15);
static int8_t buff_send[8] = {}; //buffer untuk pengiriman perintah    
 
/************ Command byte **************************/
#define lagu_berikutnya     0X01 
#define lagu_sebelumnya    0X02
#define volume_naik     0X04
#define volume_turun   0X05
 
#define reset_mp3         0X0C
#define mainkan         0X0D
#define pause_mp3         0X0E
#define mainkan_folder 0X0F
 
#define SEL_DEV        0X09
#define DEV_TF            0X02

//pin 5 enable prox
#define SET 6
#define SS_PIN 53
#define kamera 34
#define volt A0
#define volt1 A1
#define nyalamobil 32
#define pinsabuk 36
#define msin 24
#define caki 7
//#define starting 31

int tolkanan = 0;

int dataserver;
int mmesin= 0;

int panjangrfid;
int start;
int sabuk = 0;
int injakr =0; 
int injakl =0;
int tegangan = 0;
int tegangan1 = 0;
int detecttrack = 0;
int deteksirfid=0;
int leh;
int majumundur = 0;
int notag=0;
int notag2=0;
int realtag1=0;
int realtag2=0;
int count=0;
int count2=0;
int tagtrack=0;
int stepp = 0;

float tegaki = 0.0;
float tegaki1 = 0.0;

String kirimnama;
String car = "1";
String nama = "c_";
String str_sabuk;
String str_mesin;
String str_mobil;
String str_tegaki;
String str_tegaki1;
String rfidtrek;
String kirim;
String encoder;
String s;
String rfiddataa;
String st;
String no1;
String no2;

char id[9];
char csabuk[2] ;
char cmesin[2] ;
char ckirim[39];
char co;
char crfid[7];
char ctegaki[5];
char ctegaki1[5];
char cleh[2];
unsigned char ctagg;

volatile long counter = 0;
volatile long oldcounter = 0;
long selisih,selisih2,maju,mundur;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() 
{
  
//  Serial.begin(9600);             // Serial port to computer
//  HC12.begin(9600);
//  UHF.begin(57600);
//  mp3module.begin(9600);
  Serial.begin(9600); //just serial
  Serial1.begin(9600); //HC12
  Serial2.begin(9600); //mp3 player
  Serial3.begin(57600); //UHF RFID
  SPI.begin();
  mfrc522.PCD_Init();

//  pinMode(starting,OUTPUT);
  pinMode(kamera,OUTPUT);
  pinMode(nyalamobil,OUTPUT);
  pinMode(SET,OUTPUT);
  pinMode(pinsabuk,INPUT_PULLUP);
  pinMode(msin,INPUT);
  pinMode(caki,OUTPUT);
  attachInterrupt(0,ai0,RISING);
  attachInterrupt(1,ai1,RISING);
//  digitalWrite(starting, HIGH);
  digitalWrite(SET, HIGH);
  digitalWrite(nyalamobil,LOW);
  digitalWrite(kamera, LOW);
  digitalWrite(caki,LOW);
  kirimperintah(SEL_DEV, DEV_TF);

}
void loop() 
{
//    delay(100);
    mobilstart();
//    delay(10);
    voice_command();
//    delay(10);
    id_mobil();
//    delay(10);
    rfiddata();
//    delay(10);
    seat_belt();
//    delay(10);
    rfid_trek();
//    delay(10);
    mm_mesin();
//    delay(10);
    mm_mobil();
//    delay(10);
    bacategangan();
//    delay(10);
    senddata();
    delay(50);
    kirimnama  ="";
    str_sabuk ="";
    str_mesin ="";
    str_mobil ="";
    kirim="";
    s="";
    co="";  
    st = ""; 
}
