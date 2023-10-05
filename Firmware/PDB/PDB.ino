#include <Wire.h>

#define expander B0100000 //hardwired ID of the expander

#define D1 A0
#define D2 15
#define D3 14
#define D4 9
#define BUZZER 10
#define Cell1 A3
#define Cell2 A2
#define Cell3 A1
#define TOGGLE 16
#include "array.h"
#include "functions.h"

void setup() {     
  //Serial.begin(9600);   
  Serial1.begin(9600); //Use serial1 to print out through tx/rx and FTDI chip to USB-A  

  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT); 

  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(BUZZER, OUTPUT);

  pinMode(TOGGLE, OUTPUT);

  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  
  Wire.begin();

  displayString("iiii", 1000);
  reset();
  tone(BUZZER, 440);
  delay(500);  
  noTone(BUZZER);
  delay(1000);
}

char network_switch = -1;
float ref = 5.16;

void loop() {
  float r_v1 = average(Cell1, 50);
  float v_v1 = r_v1 * (4*ref)/1023.0;
  String o_v1 = DisplayChars(String(v_v1));
  
  float r_v2 = average(Cell2, 50);
  float v_v2 = (r_v2 * (4*ref)/1023.0) - v_v1;
  String o_v2 = DisplayChars(String(v_v2));
  
  float r_v3 = average(Cell3, 50);
  float v_v3 = (r_v3 * (4*ref)/1023.0) - v_v2 - v_v1;
  String o_v3 = DisplayChars(String(v_v3));
  
  float r_all = average(Cell3, 50);
  float v_all = r_v3 * (4*ref)/1023.0;
  String o_all = DisplayChars(String(v_all));

  if (v_all < 11.5 || v_v1 < 3.8 || v_v2 < 3.8 || v_v3 < 3.8) {
    tone(10, 800);
  } else if (v_all > 12 && v_v1 > 4.0 && v_v2 > 4.0 && v_v3 > 4.0) {
    noTone(BUZZER);
  }
  
  Serial.println(digitalRead(TOGGLE));
  
  displayString("CEL1", 2000);
  displayString(o_v1, 2000);
  displayString("CEL2", 2000);
  displayString(o_v2, 2000);
  displayString("CEL3", 2000);
  displayString(o_v3, 2000);
  displayString("ALL ", 2000);
  displayString(o_all, 2000);
  /*
  int value = analogRead(Cell3);
  float voltage = value * (4*ref/1023);
  String voltage_s = DisplayChars(String(voltage));
  String ref_s = DisplayChars(String(ref));
  displayString("CEL3", 500);
  displayString(voltage_s, 500);
  displayString("4444", 500);
  displayString(ref_s, 500);
  if (voltage > 2.5) { //We will input 2.5v, should read 511 or 512
    ref -= 0.01;
  } else if (voltage < 2.5) {
    ref += 0.01;
  }
  */
}

void displayString(String phrase, int length) {
  for (int i = 0; i < length/8; i++) {

/*  This code controls what is output when the network switch is flipped.
    This will poll approximately once every 5 ms. */
    if (digitalRead(TOGGLE) != network_switch) {
      network_switch = digitalRead(TOGGLE);
      Serial1.println(digitalRead(TOGGLE));
    }


    printDigit(phrase[0], D1);
    delay(1);
    printDigit(phrase[1], D2);
    delay(1);
    printDigit(phrase[2], D3);
    delay(1);
    printDigit(phrase[3], D4);
    delay(1);
  }
}


/* gets the average values from an analog pin.
   Returns the averaged value of the pin. */
float average(int pin, int samples) {
  float sum = 0.0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
  }
  float average = sum / samples;
  return average;
}

void expanderWrite(byte _data) {
  Wire.beginTransmission(expander);
  Wire.write(_data);
  Wire.endTransmission(); 
}

void reset() { 
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  expanderWrite(0b11111111);
}

int printDigit(char Chara, int digitPort) { 
  reset(); 
  int character = -1;
  digitalWrite(digitPort, HIGH);
  for(int i = 0 ; i < charsInArray ; i++) {
    if (Chara == Char[i][1]) {
     character = i;
    }
  }
  expanderWrite(~Char[character][0]);
}
