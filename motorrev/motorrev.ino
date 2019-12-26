  #include <SPI.h>
//#include <RFID.h>
//#include <IRremote.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

#define RST_PIN 4
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
//pin 5 enable prox
#define SET 6
#define STR  28
#define STL  26
#define SS_PIN 53
#define kamera 34
//pin 11,12,13 utk RFID
#define right 22
#define left  24
//#define lajur A2
#define IRRX_PIN 5
#define volt A0
#define volt1 A1
#define nyalamotor 32
#define buzzer 30

//int IRRX_PIN = 5;
//int STL = A3;
const int pdr = A3;
const int pdl = A4;
int tolkanan = 0;
int VPDR = 0;
int VPDL = 0;
int VSTR = 0;
int VSTL = 0;
int dataserver;
int x=0;
int y=0; 
int trekid= 0;
int tolehr = 0;
int tolehl= 0;
int panjangrfid;
int start;
int pedall = 0;
int pedalr = 0;
int injakr =0; 
int injakl =0;
int tegangan = 0;
int tegangan1 = 0;
int detecttrack = 0;
int buz=0;
int leh;

float tegaki = 0.0;
float tegaki1 = 0.0;

String kirimnama;
String mtr = "1";
String nama = "m_";
String str_pdr;
String str_pdl;
String str_str;
String str_stl;
String str_tegaki;
String str_tegaki1;
String trek;
String str_tolehr;
String str_tolehl;
String kirim;
String fin;
String s;
String rfiddataa;
String str_leh;

char id[9];
char cpdr[2] ;
char cpdl[2] ;
char cstr[2] ;
char cstl[2] ;
char ctolehr[2];
char ctolehl[2];
char ctrek[3];
char ckirim[39];
char co;
char crfid[7];
char ctegaki[5];
char ctegaki1[5];
char cleh[2];

bool bacasensor;

IRrecv irrecv(IRRX_PIN);
decode_results results;

IRsend irsend;

//RFID rfid(SS_PIN, RST_PIN);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void(* resetFunc) (void) = 0;
void setup() 
{
  
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);     
  pinMode(0,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(STR, INPUT);
  pinMode(STL, INPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(kamera,OUTPUT);
  pinMode(nyalamotor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(SET,OUTPUT);
  digitalWrite(SET, HIGH);
  digitalWrite(right,LOW);
  digitalWrite(left,LOW);
  digitalWrite(nyalamotor,LOW);
  digitalWrite(kamera, LOW);

  irrecv.enableIRIn();
  digitalWrite(IRRX_PIN, HIGH); // Optional Internal Pull-up
  SPI.begin();
  mfrc522.PCD_Init();
  tolehr = 0;
  tolehl = 0;
  start = 0;
  bacasensor= false;
}
void loop() 
{
    delay(100);
    motorstart();
    delay(10);
    id_motor();
    delay(10);
   rfiddata();
    delay(10);
    ir();
    delay(10);
    stang();
    delay(10);
    bacategangan();
    delay(10);
    senddata();
    delay(100);
    kirimnama  ="";
    str_tolehr ="";
    str_tolehl ="";
    rfiddataa ="";
    trek="";
    kirim="";
    s="";
    co="";   
}
