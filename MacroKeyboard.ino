#include <Keyboard.h>

char ctrlKey { KEY_LEFT_CTRL };
char altKey { KEY_LEFT_ALT };
char shiftKey { KEY_LEFT_SHIFT };


const char keys[2][5] = {{'a' , 'b', 'c', 'd', 'e' } , {'f' , 'g', 'h', 'i', 'j' }};

void setup() {
  //Config all pins for 
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  for (int i { 6 } ; i <= 10 ; i ++ ){
    pinMode(i, INPUT);
  }
}

void loop() {
  
  //Cylce though all the rows first, 
  for (int i { 4 } ; i <= 5 ; i++){
    digitalWrite(i, HIGH);
    //Cylcle though all the colums second
    for (int j { 6 } ; j <= 10 ; j++){
      //read each pin and then take action based on what i is
      if (digitalRead(j) == HIGH) {
        keyboardOut(j , i-4, j -6);
      }
    } 
    digitalWrite(i,LOW);
  }
  delay(10);
} 

void keyboardOut(int pinRef, int r, int c) {
  Keyboard.press(ctrlKey);
  Keyboard.press(shiftKey);
  Keyboard.press(altKey);
  Keyboard.press(keys[r][c]);
  Serial.println( "Pressing the key: "); Serial.print( keys[r][c]);
  
  Keyboard.releaseAll();
  
  while (digitalRead(pinRef) == HIGH ){
    delay(10);
    //to avoid dupiclate outptus don't do anything until this key has been released
  }
}
