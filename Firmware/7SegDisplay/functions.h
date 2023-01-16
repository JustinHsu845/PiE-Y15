//Created by aboda243
//Modified by Justin H. for Pioneers in Engineering
//Used in Pioneer in Engineering's battery display on PDB
//https://create.arduino.cc/projecthub/aboda243/how-to-use-4-digit-7-segment-without-library-b8e014

void reset() { 
  digitalWrite(D1, !mode);
  digitalWrite(D2, !mode);
  digitalWrite(D3, !mode);
  digitalWrite(D4, !mode);
  for(byte i = 0 ; i < 8 ; i++){
    digitalWrite(seg[i], mode); //mode = 1; for each segment, 1 = off and 0 = on
  }
}

void printDigit(char Chara, int digitPort) { 
  reset(); 
  int character = -1;
  digitalWrite(digitPort, mode);
  for(int i = 0 ; i < charsInArray ; i++) {
    if (Chara == Char[i][8]) { //set character equal to the corresponding array index
     character = i;
    }
  }
  for (int i = 0; i < 8; i++) { //iterate through each segment for the digit, setting on or off as defined by array.h
    if (mode == common_anode) {
      digitalWrite(seg[i],!Char[character][i]); 
    }   
    else if (mode == common_cathode) {
      digitalWrite(seg[i], Char[character][i]);
    }
  }
}

char convert(char number) { //converts input char to another char
  if (isdigit(number)) {
    String alphabet = "abcdefghijklmnopqrstuvwxyz";
    return alphabet.charAt((int) (number - '0'));
  } else {
    return number;
  }
}

String removeChar(String phrase, char remove) {
  String newPhrase = "    ";
  int k = 0;
  for (int i = 0; i < phrase.length(); i++) {
    if (phrase.charAt(i) != remove) {
      newPhrase[k] = phrase[i];
      k += 1;
    }
    if (k == digits) {
      break;
    }
  }
  return newPhrase;
}

void printDisplay(String Phrase, int Delay) { //no scrolling
  int stringLength = Phrase.length();
  int delay_factor = digits * 2;
  int decimal_pos = -1;
  char toPrint[] = {' ', ' ', ' ', ' '};

  for (int i = 0; i < digits + 1; i++) {
    if (Phrase.charAt(i) == '.') { //only supports 1 decimal point
      stringLength -= 1;
      decimal_pos = i;
      break;
    }
  }
  Phrase = removeChar(Phrase, '.');

  for(int i = 0; i < digits; i++) {
    if (i+1 <= stringLength && decimal_pos == i+1) {
      toPrint[i] = convert(Phrase[i]);
    } else if (i+1 <= stringLength) {
      toPrint[i] = Phrase[i];
    }
  }
for(int ti = 0 ; ti <= (Delay / delay_factor) ; ti++) { //continously flashes characters for DELAY duration
    printDigit(toPrint[0], D1);
    delay(2);
    printDigit(toPrint[1], D2);
    delay(2);
    printDigit(toPrint[2], D3);
    delay(2);
    printDigit(toPrint[3], D4);
    delay(2);
  }
} 