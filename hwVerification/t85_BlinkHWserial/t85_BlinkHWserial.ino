char foo;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0,HIGH);
  delay(100);
  digitalWrite(0,LOW);
  delay(200);
  Serial.println("SERIAL MESSAGE WOW");
}
