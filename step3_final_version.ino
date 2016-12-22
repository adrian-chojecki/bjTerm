const int sensorCount = 3;
const int barGraphSize = 9;

int sensor[sensorCount];
int sensorRead[sensorCount];
int voltageDrop[sensorCount];
float temperature[sensorCount];

int ledPins[barGraphSize];

void setup() {
  Serial.begin(9600);

  //internal reference 1.1V
  //we are measuring very low signal and have only 8bit ADC
  analogReference(INTERNAL);

  //sensor inputs
  sensor[0] = A0;
  sensor[1] = A1;
  sensor[2] = A2;

  //led outputs for bargraph
  ledPins[0] = 2;
  ledPins[1] = 3;
  ledPins[2] = 4;
  ledPins[3] = 5;
  ledPins[4] = 6;
  ledPins[5] = 7;
  ledPins[6] = 8;
  ledPins[7] = 9;
  ledPins[8] = 10;
  
  
  //set outputs mode for bragraph
  for (int thisLed = 0; thisLed < barGraphSize; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop() {

  for (int i = 0; i < sensorCount; i++) {
  
    sensorRead[i] = analogRead(sensor[i]);
    
    //map ADC value to volatage drop on transistor/diode
    //
    //MAGIC NUMBER 8 - using full range of int, minimize rounding erros
    voltageDrop[i] = map(sensorRead[i], 0, 1023, 0, 1100 * 8);
   
    //map voltage drop to temperature
    //MAGIC NUMBER 8 - using full range of int, minimize rounding erros
    //range for volatege drop for BC547 transistor
    temperature[i] = fmap((float)voltageDrop[i], 715 * 8, 495 * 8, -10, 100);
  }

  Serial.println("-----------------------------");

  for (int i = 0; i < sensorCount; i++) {
    Serial.print("sensor #");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(temperature[i]);
  }


  float meanTemperature = 0.0f;
  for (int i = 0; i < sensorCount; i++) {
    meanTemperature += temperature[i];
  }

  meanTemperature /= sensorCount;

  Serial.print("mean: ");
  Serial.println(meanTemperature);

  
  //meanTemperature to bargraph
  int bargraph = map(meanTemperature, 16, 24, 0, barGraphSize);

  for (int thisLed = 0; thisLed < barGraphSize; thisLed++) {

    if (thisLed < bargraph)
      digitalWrite(ledPins[thisLed], LOW);

    else
      digitalWrite(ledPins[thisLed], HIGH);

  }

  delay(300);
}


//implementation of map() function for float
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
