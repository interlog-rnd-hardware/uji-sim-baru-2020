/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>
#include <Wire.h>
int RECV_PIN = 11;
int x = 0;
byte kiri = 0;
byte kanan = 0;
byte deff = 0;
IRrecv irrecv(RECV_PIN);

decode_results results;
void(* resetFunc) (void) = 0;
void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
    Wire.begin();
    kiri = 0;
    kanan = 0;
}

void loop() {
  if (irrecv.decode(&results)) {
//    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);

  
//  Serial.print(resu/lts.value);
  if (results.value == 428919)
  {
//    Serial.println("kanan");
    kanan=1;
//    Wire.beginTransmission(9); // transmit to device #9
//    Wire.write("kiri ");
//    Wire.write(kiri);
//    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write("kanan ");
    Wire.write(kanan);
    Wire.endTransmission();    // stop transmitting
    Serial.println("kanan");
  }
  else if (results.value == 428946)
  {
    kiri = 1;
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write("kiri ");
    Wire.write(kiri);
    Wire.endTransmission();    // stop transmitting
//    Wire.beginTransmission(9); // transmit to device #9
//    Wire.write("kanan ");
//    Wire.write(kanan);
//    Wire.endTransmission();    // stop transmitting
    Serial.println("kiri");
  }
  if (kiri == 1 && kanan == 1)
  {
    kiri = 0;
    kanan = 0;
//    Serial.println("udah 1 semua");
    delay(100);
    resetFunc();
  }
  else if(kiri == 0 && kanan == 0)
  {
    Serial.println("0 semua");
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write("kiri ");
    Wire.write(deff);
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write("kanan ");
    Wire.write(deff);
    Wire.endTransmission();    // stop transmitting
  }
  Serial.print(kiri);
  Serial.print(" ");
  Serial.println(kanan);
//  Wire.endTransmission();    // stop transmitting
//  x++; // Increment x
//  if (x > 5) x = 0; // `reset x once it gets 6
  delay(500);
}
