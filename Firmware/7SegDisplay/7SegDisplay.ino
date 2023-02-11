//Created by aboda243
//Modified by Justin H. for Pioneers in Engineering
//Used in Pioneer in Engineering's battery display on PDB
//https://create.arduino.cc/projecthub/aboda243/how-to-use-4-digit-7-segment-without-library-b8e014

#include <Wire.h>

#define expander B0100000 

#define D1 A0
#define D2 15
#define D3 14
#define D4 9
#define BUZZER 10
#define Cell1 A3
#define Cell2 A2
#define Cell3 A1
#include "array.h"
#include "functions.h"

//test push
void setup() {                

  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT); 
  Serial.begin(9600);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  Wire.begin();
}
//long previousTime = 0;
// the loop routine runs over and over again forever:
void loop() {
  //unsigned long currentTime = millis();
  analogReference(DEFAULT);
  //float* voltages = parseVoltage(analogRead(Cell1), analogRead(Cell2), analogRead(Cell3));
  float r_v1 = average(Cell1, 50);
  float v_v1 = r_v1 * 20.0/1023.0;
  String o_v1 = DisplayChars(String(v_v1));
  
  float r_v2 = average(Cell2, 50);
  float v_v2 = (r_v2 * 20.0/1023.0) - v_v1;
  String o_v2 = DisplayChars(String(v_v2));
  
  float r_v3 = average(Cell3, 50);
  float v_v3 = (r_v3 * 20.0/1023.0) - v_v2 - v_v1;
  String o_v3 = DisplayChars(String(v_v3));
  
  float r_all = average(Cell3, 50);
  float v_all = r_v3 * 20.0/1023.0;
  String o_all = DisplayChars(String(v_all));

  tone(10, 1000);
  //else if (v_all > 12 && v_v1 > 4.0 && v_v2 > 4.0 && v_v3 > 4.0) {
    //noTone(BUZZER);
  //}
  //Serial.println(o_v1);
  
  displayString("CEL1", 2000);
  displayString(o_v1, 2000);
  displayString("CEL2", 2000);
  displayString(o_v2, 2000);
  displayString("CEL3", 2000);
  displayString(o_v3, 2000);
  displayString("ALL ", 2000);
  displayString(o_all, 2000);

}

void displayString(String phrase, int length) {
  for (int i = 0; i < length/8; i++) {
    printDigit(phrase[0], D1);
    delay(2);
    printDigit(phrase[1], D2);
    delay(2);
    printDigit(phrase[2], D3);
    delay(2);
    printDigit(phrase[3], D4);
    delay(2);
  }
}

/* Voltage divider divides voltages by 4.
   outputs voltage of the 3 cells in a float array. */
String* parseVoltage(int pin1, int pin2, int pin3) {

  float r_v1 = average(Cell1, 100);
  float v_v1 = r_v1 * 20.0/1023.0;
  String o_v1 = DisplayChars(String(v_v1));
  
  float r_v2 = average(Cell2, 100);
  float v_v2 = (r_v2 * 20.0/1023.0) - v_v1;
  String o_v2 = DisplayChars(String(v_v2));
  
  float r_v3 = average(Cell3, 100);
  float v_v3 = (r_v3 * 20.0/1023.0) - v_v2 - v_v1;
  String o_v3 = DisplayChars(String(v_v3));
  
  float r_all = average(Cell3, 100);
  float v_all = r_v3 * 20.0/1023.0;
  String o_all = DisplayChars(String(v_all));
  
  String output[] = {o_v1, o_v2, o_v3, o_all};
  return output;
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
  //for(byte i = 0 ; i < 8 ; i++){
    //digitalWrite(seg[i], HIGH); //mode = 1; for each segment, 1 = off and 0 = on
  //}
}

int printDigit(char Chara, int digitPort) { 
  reset(); 
  int character = -1;
  digitalWrite(digitPort, HIGH);
  for(int i = 0 ; i < charsInArray ; i++) {
    if (Chara == Char[i][1]) { //set character equal to the corresponding array index
     character = i;
    }
  }
  expanderWrite(~Char[character][0]);
  
}
