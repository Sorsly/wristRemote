#include <SoftwareSerial.h>

#define rxPin 6
#define txPin 7

char foo;

SoftwareSerial mySerial(rxPin,txPin);
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(13,OUTPUT);
  Serial.print("serial monitor connection works");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available() > 0) {
    foo = mySerial.read();
    Serial.print(foo);
  }
}
