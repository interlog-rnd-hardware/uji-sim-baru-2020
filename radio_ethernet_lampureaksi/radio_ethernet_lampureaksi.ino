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
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.korlantas.id";    // name address for Google (using DNS)
const char* php = " /lampureaksi.php";
const int port   = 80;

String mood = "najib_ganteng";
String respon,respon1,respon2,respon3,respon4,respon5,finish,belok,s,sub;
int panjang,panjang1,panjang2,panjang3,panjang4,panjang5;
bool m1,m2,m3,m4,mm1,mm2,mm3,mm4,m5,rc,bkanan,bkiri;
char cc[2];

int jmlhkirim = 0;

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
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
if (client.connect(server, 80)) {  
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
  String url; 
  url += php;
  url += "?mood";
 // url += mood; 
  
  client.print("GET"); // /chiller.php?mood=najib_ganteng
  client.print(url);
  client.println(" HTTP/1.1");
  client.println("Host: korlantas.id");
  client.println("Connection: close");
  client.println();
  Serial.println(url);
  //return true;
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

 
  beginMicros = micros();
}

void loop() {
  int len = client.available();
  if (len) {
    byte buffer[250];
    char c[250];
    if (len > 250) len = 250;
    client.read(c, len);
    if (printWebData) {
      //Serial.write(c, len); // show in the serial monitor (slows some boards)
      String data = String(c);
      String datakirim = data.substring(246,247);
      Serial.println(datakirim);
      if(datakirim == "1" || datakirim == "2")
      {
        HC12.println(datakirim);
        jmlhkirim = 0;
      }

      if(datakirim == "0" && jmlhkirim == 0)
      {
        HC12.println(datakirim);
        jmlhkirim = 1;
      }
    }
    byteCount = byteCount + len;
    //break;
    //buffer="";
  }
  

//   if (!client.connected()) {
//    endMicros = micros();
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//    Serial.print("Received ");
//    Serial.print(byteCount);
//    Serial.print(" bytes in ");
//    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
//    Serial.print(seconds, 4);
//    float rate = (float)byteCount / seconds / 1000.0;
//    Serial.print(", rate = ");
//    Serial.print(rate);
//    Serial.print(" kbytes/second");
//    Serial.println();
//  }

  if (client.connect(server, 80)) {  
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
  String url; 
  url += php;
  url += "?mood";
 // url += mood; 
  
  client.print("GET"); // /chiller.php?mood=najib_ganteng
  client.print(url);
  client.println(" HTTP/1.1");
  client.println("Host: korlantas.id");
  client.println("Connection: close");
  client.println();
  Serial.println(url);
  //return true;
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

 
  delay(100);
  s = "";
}
