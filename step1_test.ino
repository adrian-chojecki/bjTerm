//pin connected to sensor
const int analogPin = A0;

void setup() {
   Serial.begin(9600);  

   //internal reference 1.1V
   //we are measuring very low signal and have only 10bit ADC
   analogReference(INTERNAL);
}

void loop() {

  unsigned int sensorRead = analogRead(analogPin);

  //map ADC value to volatage drop on transistor/diode
  int voltageDrop = map(sensorRead, 0, 1023, 0, 1100);
  
  Serial.print("ADC:");
  Serial.print(sensorRead);
  Serial.print("  voltageDrop:");
  Serial.print(voltageDrop);
  Serial.println(" mV");
  Serial.println("-----------------------------");

  delay(300);
}
