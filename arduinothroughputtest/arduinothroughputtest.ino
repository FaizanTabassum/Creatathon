int analogPin = A0;
String recieveString;
int numBurstSamples;
unsigned long timeStart;
unsigned long timeStop;
unsigned long timeElapsed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  pinMode(analogPin, INPUT);
}

void loop() {
  // check pc send command

  if (Serial.available()) {
    recieveString = Serial.readString();
    if (recieveString.startsWith("B")) {
      timeStart = micros();
      numBurstSamples = recieveString.substring(1).toInt();
      Serial.println(numBurstSamples);
      GrabBurstandSend(numBurstSamples);
    }
    timeStop = micros();
    timeElapsed = timeStop - timeStart;
    Serial.print("Time = ");
    Serial.println(timeElapsed);
  }
}

void GrabBurstandSend(int numSamples) {
  unsigned int val[numSamples];
  unsigned long time[numSamples];

  for (int i = 0; i < numSamples; i++) {
    val[i] = analogRead(analogPin);
  }

  for (int i = 0; i < numSamples; i++) {
    Serial.print(time[i]);
    Serial.print(" , ");
    Serial.println(val[i]);
  }
  Serial.println("END");
}