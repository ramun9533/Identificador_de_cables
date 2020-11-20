
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


int a=13;
int b;
int c;
int d;
int e;
int f;

 int H;
BluetoothSerial SerialBT;

void setup() {
Serial.begin(115200);
 SerialBT.begin("ESP32prueba");
  Serial.println("Listo");
pinMode (a,OUTPUT);
pinMode (b,OUTPUT);
pinMode (c,OUTPUT);
pinMode (d,OUTPUT);
pinMode (e,OUTPUT);
pinMode (f,OUTPUT);

}

void loop() {
//if (Serial.available()) {
  //  SerialBT.write(Serial.read());
  //}
  
  H=Serial.read();

 while (SerialBT.available()) {    //pregunto sobre el dato del serial
    char data = (char)SerialBT.read();
    if ( data == 'a')
    { digitalWrite(a, !digitalRead(a));
   } }
//switch (H) {
  //case 'a':
  //digitalWrite (a, HIGH);
  //break;
//case 'b':
  //digitalWrite (b, HIGH);
 // break;
 // case 'c':
  //digitalWrite (c, HIGH);
  //break;
 // case 'd':
 // digitalWrite (d, HIGH);
  //break;
  //case 'f':
  //digitalWrite (f, HIGH);
  //break;




  
//}


if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);







}
