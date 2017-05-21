/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#include <SoftwareSerial.h>

//software serial for the attiny85
#define rxPin 3
#define txPin 4

SoftwareSerial t85Serial(rxPin, txPin);

//pushbutton values (mV) based on resistors
/* all combinations tested; all push buttons
 *  are unique/no interference. If resistance
 *  values are changed, make sure that values
 *  are as evenly spread as possible
 */
int pb0 = 528;  //1000  ohm
int pb1 = 349;  //2200  ohm
int pb2 = 268;  //3300  ohm
int pb3 = 212;  //4700  ohm

//setting values
int flag;
int flagLast = -1;

//threshold values
int thrErr = 20;  //threshold
unsigned long thrDbnce = 50;

//time values (millis())
unsigned long timDbnce = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize t85Serial communication at 9600 bits per second:
  t85Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 3 (ADC3)(hw pin 2):
  int pbVal = analogRead(3);

  t85Serial.print("raw sensor value: ");
  t85Serial.print(pbVal);  //print raw sensor value
  delay(1);        // delay in between reads for stability
  
  if(pbVal > pb0 - thrErr && pbVal < pb0 + thrErr) {
    flag = 0;
  } else if(pbVal > pb1 - thrErr && pbVal < pb1 + thrErr) {
    flag = 1;
  } else if(pbVal > pb2 - thrErr && pbVal < pb2 + thrErr) {
    flag = 2;
  } else if(pbVal > pb3 - thrErr && pbVal < pb3 + thrErr) {
    flag = 3;
  } else {
    flag = -1;
  }

/*
  if(flag != flagLast) {151
    timDbnce = millis();
  }
  if((millis() - timDbnce) > thrDbnce) {
    if(pbVal != pbState) {
      pbState = pbVal;
    }
      if(pbState == 
  }
  */
  t85Serial.print("\tflag: ");
  t85Serial.println(flag);
  
}
