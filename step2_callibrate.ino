//pin connected to sensor
const int analogPin = A0;

void setup() {
   Serial.begin(9600);  

   //internal reference 1.1V
   //we are measuring very low signal and have only 8bit ADC
   analogReference(INTERNAL);
}

void loop() {

  unsigned int sensorRead = analogRead(analogPin);

  //map ADC value to volatage drop on transistor/diode
  //
  //MAGIC NUMBER 8 - using full range of int, minimize rounding erros
  int voltageDrop = map(sensorRead, 0, 1023, 0, 1100*8);

  //map voltage drop to temperature
  //MAGIC NUMBER 8 - using full range of int, minimize rounding erros
  
  //range for volatege drop for BC547 transistor
  float temperature = fmap((float)voltageDrop, 715*8, 495*8, -10, 100);
  
  Serial.print("ADC:");
  Serial.print(sensorRead);
  
  Serial.print("  voltageDrop:");
  Serial.print(voltageDrop);
  Serial.println(" mV");
  
  Serial.print("temperature:");
  Serial.print(temperature);
  Serial.println("deg. C");
  Serial.println("-----------------------------");

  delay(1000);
}


//implementation of map() function for float
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
