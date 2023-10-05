void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

int counter = 0;
float ref = 5.000;
void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A1);
  float voltage = value * (ref/1023);
  Serial.print("Reading: ");
  Serial.print(voltage);
  Serial.println("v");
  Serial.print("Ref: ");
  Serial.print(ref);
  Serial.println("v");
  if (voltage > 2.5) { //We will input 2.5v, should read 511 or 512
    ref -= 0.005;
    Serial.print("Calibration (overshoot) attempt: ");
    Serial.println(counter);
  } else if (voltage < 2.5) {
    ref += 0.005;
    Serial.print("Calibration (undershoot) attmpt: ");
    Serial.println(counter);
  } else {
    Serial.println("Calibration Complete!");
  }
  counter += 1;
  delay(100);
}
