/*
  Web client
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 */

#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "korlantas.id";    // name address for Google (using DNS)
const char* phpinsert = " /motor.php";
const char* phpselect = " /relay1.php";
const int port   = 80;

String nocones;
String statuss;
String tegangan;
String datamotor;
String variabel;
String nilai = "";
String Respon = "";
String respon,respon1,respon2,respon3,respon4,respon5,finish,belok,s,sub;
String perangkat = "m_1";
int panjang,panjang1,panjang2,panjang3,panjang4,panjang5;

bool statusKomunikasiWifi = false;
bool responDariServer = false;
bool m1,m2,m3,m4,mm1,mm2,mm3,mm4,m5,rc,bkanan,bkiri;
char cc[2];

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  HC12.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(100);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}

void loop() {
Serial.println();
delay(1000);                          //Keeps the connection from freezing

//if (client.connect(server ,80)) {
Serial.println("Connected");

//client.print("GET 192.168.0.101:8080/aquarium_light_read.php ");
client.println("GET /relay1.php HTTP/1.1");



//Serial.println("Finish");

//client.println(" HTTP/1.1");
client.println("Host: korlantas.id");
client.println("Connection: close");
client.println();
client.println();
Serial.println("nilainya ");
 unsigned long timeout = millis();
 while (client.available() == 0) {
  if (millis() - timeout > 5000) {
    Serial.println("Client timeout");
    client.stop();
    return;
  }
 }
  while (client.available())
  {   
    Serial.print(client.readString());    
  }
//}

//else
//{
//Serial.println("Connection unsuccesful");
//}
 //stop client
 delay(1000);
client.stop();
 while(client.status() != 0)
{
  delay(5);
}

  
//    while (HC12.available()) 
//    {
//      char mot = HC12.read();
//      datamotor += mot;
//    }
//    
//      //Serial.println(datamotor);
//      if(datamotor.length() > 30)
//      {
//       statusKomunikasiWifi = keDatabase(datamotor);
//      }
//      statusKomunikasiWifi = relay(perangkat);
//    // if there are incoming bytes available
//    // from the server, read them and print them
//    if(statusKomunikasiWifi)
//    {
//     while (client.available()) 
//    {
//      char c = client.read();
//      Respon += c;
//    }
//    
//    // if the server's disconnected, stop the client
//    if (!client.connected()) {
//      Serial.println("Disconnecting from server...");
//      client.stop();
//      statusKomunikasiWifi = false;
//      responDariServer = true;
//    }
//    }
//   
//  
//
//  if(responDariServer)
//  {
//responDariServer = false;
//    //Serial.println(Respon);
//    int posisiData = Respon.indexOf("\r\n\r\n");
//    String Data = Respon.substring(posisiData+4);
//    Serial.println(Data);
//    Data.trim();
// 
//    String variabel;
//    String nilai;
// 
//    Serial.println("Data dari server");
//    posisiData = Data.indexOf('=');
//    if(posisiData > 0)
//    {
//      variabel = Data.substring(0,posisiData);
//      nilai = Data.substring(posisiData+1);
//   
//      //===========Penanganan respon disini
//      Serial.print(variabel);
//      Serial.print(" = ");
//      Serial.println(nilai);
//  }
//  delay(150);
//  Respon = "";
//}
}

bool relay(String perangkat)
{
  // if you get a connection, report back via serial
        if (client.connect(server, 80)) 
        {
         Serial.print("connected to ");
         Serial.println(client.remoteIP());
      // Make a HTTP request:
         String url; 
         url += phpselect;
         url += "?motor=";
         url += perangkat;
   
         client.print("GET"); // /chiller.php?mood=najib_ganteng
         client.print(url);
         client.println(" HTTP/1.1");
         client.println("Host: korlantas.id");
         client.println("Connection: close");
         client.println();
         client.stop();
         Serial.println(url);
         datamotor = "";
         return true;
         }
  return false;
}

 bool keDatabase(String datamotor)
 {  
 String url; 
        if (client.connect(server, 80)) 
        {
         Serial.print("connected to ");
         Serial.println(client.remoteIP());
      // Make a HTTP request:
         String url; 
         url += phpinsert;
         url += "?motor=";
         url += datamotor;
   
         client.print("GET"); // /chiller.php?mood=najib_ganteng
         client.print(url);
         client.println(" HTTP/1.1");
         client.println("Host: korlantas.id");
         client.println("Connection: close");
         client.println();
         Serial.println(url);
         datamotor = "";
         return true;
         }
         return false;
}
