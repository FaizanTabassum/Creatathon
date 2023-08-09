int analogPin = A0;
String recieveString;
int numBurstSamples = 500;

#define cbi(sfr,bit) (_SFR_BYTE(sfr)&=~_BV(bit))
#define sbi(sfr,bit) (_SFR_BYTE(sfr)|=_BV(bit))
unsigned long burstDurationmsec = 0;// we select an unsigned long because we recieve a 32 bit number from the application and int is only 16 bit
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  pinMode(analogPin, INPUT);
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
 }

void loop() {
  // check pc send command

  if (Serial.available()) {
    recieveString = Serial.readStringUntil('\n');// tells the arduino when the string ends that we have sent and we check for a null character because it is better than a delay
    if (recieveString.startsWith("S")) {
      numBurstSamples = recieveString.substring(1).toInt();
    }
    else if (recieveString.startsWith("B")) {
      burstDurationmsec = recieveString.substring(1).toInt();
      GrabBurstandSend();
    }
  }
}

void GrabBurstandSend() {
  unsigned int val[numBurstSamples];
  unsigned long burstSamplesDelayusec = ((1000*(burstDurationmsec))/numBurstSamples)-100;

  for (int i = 0; i < numBurstSamples; i++) {
    val[i] = analogRead(analogPin);
    delayMicroseconds(burstSamplesDelayusec);
  }

  for (int i = 0; i < numBurstSamples; i++) {
    Serial.println(val[i]);
  }
  Serial.println("END");
}