#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin
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

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.korlantas.id";    // name address for Google (using DNS)
const char* php = " /mobil.php";
const int port   = 80;

String filterrepeater,nomcones;
String nocones;
String statuss;
String tegangan;
String datacones;
String respon,respon1,respon2,respon3,respon4,respon5,finish,belok,s,sub;
int panjang,panjang1,panjang2,panjang3,panjang4,panjang5;
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
//  if (client.connect(server, 80)) {
//    Serial.print("connected to ");
//    Serial.println(client.remoteIP());
//    // Make a HTTP request:
//  String url; 
//  url += php;
//
   //motor
//  url += "?motor=";
//  url += motor;
//  url += "&idmotor=";
//  url += idmotor;
//  url += "&lihatkanan=";
//  url += lihatkanan;
//  url += "&lihatkiri=";
//  url += lihatkiri;
//  url += "&prox=";
//  url += prox;
//  url += "&track=";
//  url += track;
//  url += "&tegangan1=";
//  url += tegangan1;
//  url += "&tegangan2=";
//  url += tegangan2;
  
  //cones
//  url += "?mobil=";
//  url += nocones;
//  url += "&status=";
//  url += statuss;
//  url += "&tegangan=";
//  url += tegangan;
  
//  client.print("GET"); // /chiller.php?mood=najib_ganteng
//  client.print(url);
//  client.println(" HTTP/1.1");
//  client.println("Host: korlantas.id");
//  client.println("Connection: close");
//  client.println();
//  Serial.println(url);
//  } else {
//    // if you didn't get a connection to the server:
//    Serial.println("connection failed");
//  }
  beginMicros = micros();
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }
    while (true) {
        while (HC12.available()) 
    {
      char cone = HC12.read();
      datacones += cone;
    }
    int indexxx = datacones.indexOf('<');
    int respon = datacones.indexOf('>',indexxx+1);
    String datanya = datacones.substring(indexxx + 1, respon);
//    if (datacones.startsWith("<"))
//    {
      Serial.println(datanya);
//      if (datanya.startsWith("c_1"))
//      {
        if (client.connect(server, 80)) 
        {
          Serial.print("connected to ");
          Serial.println(client.remoteIP());
          // Make a HTTP request:
          String url; 
          url += php;
          url += "?mobil=";
          url += datanya;
  
          client.print("GET"); // /chiller.php?mood=najib_ganteng
          client.print(url);
          client.println(" HTTP/1.1");
          client.println("Host: korlantas.id");
          client.println("Connection: close");
          client.println();
          Serial.println(url);
        }
    datacones = "";
    datanya = "";
//    }
    delay(500);
//    }
//     if (!client.connected()) {
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
  }
}
