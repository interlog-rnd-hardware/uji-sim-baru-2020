  #include <SPI.h>
//#include <RFID.h>
//#include <IRremote.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

#define RST_PIN 5

SoftwareSerial HC12(12, 13); // HC-12 TX Pin, HC-12 RX Pin
SoftwareSerial mp3module(10, 11);

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
#define pinsabuk 22
#define msin 24

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

char id[9];
char csabuk[2] ;
char cmesin[2] ;
char ckirim[39];
char co;
char crfid[7];
char ctegaki[5];
char ctegaki1[5];
char cleh[2];

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup() 
{
  
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);
  mp3module.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(kamera,OUTPUT);
  pinMode(nyalamobil,OUTPUT);
  pinMode(SET,OUTPUT);
  pinMode(pinsabuk,INPUT_PULLUP);
  pinMode(msin,INPUT);
  
  digitalWrite(SET, HIGH);
  digitalWrite(nyalamobil,LOW);
  digitalWrite(kamera, LOW);
  
  kirimperintah(SEL_DEV, DEV_TF);

}
void loop() 
{
    delay(100);
    mobilstart();
    delay(10);
    voice_command();
    delay(10);
    id_mobil();
    delay(10);
    rfiddata();
    delay(10);
    seat_belt();
    delay(10);
    rfid_trek();
    delay(10);
    mm_mesin();
    delay(10);
    mm_mobil();
    delay(10);
    senddata();
    delay(100);
    kirimnama  ="";
    str_sabuk ="";
    str_mesin ="";
    str_mobil ="";
    kirim="";
    s="";
    co="";   
}
