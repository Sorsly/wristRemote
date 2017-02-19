/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

//pushbutton values (mV) based on resistors
int pb0 = 151;
int pb1 = 326;
int pb2 = 538;
int pb3 = 633;

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
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int pbVal = analogRead(A0);
  
  //Serial.println(pbVal);  //print raw sensor value
  delay(1);        // delay in between reads for stability
  
  if(pbVal > pb0 - thrErr && pbVal < pb0 + thrErr) {
    flag = 0;
  } else if(pbVal > pb1 - thrErr && pbVal < pb1 + thrErr) {
    flag = 1;
  } else if(pbVal > pb2 - thrErr && pbVal < pb2 + thrErr) {
    flag = 2;
  } else if(pbVal > pb3 - thrErr && pbVal < pb3 + thrErr) {
    flag = 3;
  } else if(pbVal == 0) {
    flag = -1;
  }

/*
  if(flag != flagLast) {
    timDbnce = millis();
  }
  if((millis() - timDbnce) > thrDbnce) {
    if(pbVal != pbState) {
      pbState = pbVal;
    }
      if(pbState == 
  }
  */
  Serial.println(flag);
  
}
