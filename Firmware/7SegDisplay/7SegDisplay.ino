//Created by aboda243
//Modified by Justin H. for Pioneers in Engineering
//Used in Pioneer in Engineering's battery display on PDB
//https://create.arduino.cc/projecthub/aboda243/how-to-use-4-digit-7-segment-without-library-b8e014

#define common_cathode 0
#define common_anode 1
#define digits 4
bool mode = common_anode;// my display is common anode
#define pinA 8
#define pinB 9
#define pinC 7
#define pinD 2
#define pinE 0
#define pinF 15
#define pinG 14
#define pinDP 1
#define D1 6
#define D2 5
#define D3 4
#define D4 3
#include "array.h"
#include "functions.h"

void setup() {                
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT); 
  pinMode(pinDP, OUTPUT);  
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT); 
  Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
  //printDisplay("C 1",2000);// use this function to print a string (has numbers, characters or phrases) when the length of string is 4 or less than 4, the second variable is the time for printing on display
  //printDisplay("1i1i", 2000);// use this function to reset the display
  //printDisplay("C  1", 2000);
  printDisplay("11i1", 2000);
  //String toPrint = "";
  //tone(Buzzer, 1000);
  
  //Serial.println(convert(0));
}
