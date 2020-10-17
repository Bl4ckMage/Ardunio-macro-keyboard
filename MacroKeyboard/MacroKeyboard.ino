//TESTING BED
#include <Keyboard.h>

bool cmdCalled { false };
const int r[2] { 6 , 7 };
const int c[4] { 8,10,11,12 };
const int rC { 2 };
const int cC { 4 };


char ctrlKey { KEY_LEFT_CTRL };
char altKey { KEY_LEFT_ALT };
char shiftKey { KEY_LEFT_SHIFT };

//const char keys[2][4] = {{'a' , 'd', 'c', 'b' } , {'e' , 'h', 'g', 'f'}};
const int keys[2][4] = {{194,197,196,195 } , {198,201,200,199}};

void setup() {
  Serial.begin(9600);
  Serial.println("Setting inputs ");
  for (int i { 0 } ; i <  rC; i++ ) {
    pinMode(r[i] , INPUT); 
    Serial.print("Pin: "); Serial.print(r[i]); Serial.print(" has been set to INPUT");
  }

  Serial.println("Setting pull ups ");
  for (int i { 0} ; i < cC; i++ ){
    pinMode(c[i] , INPUT_PULLUP);
    Serial.print("Pin: "); Serial.print(c[i]); Serial.print(" has been set to INPUT_PULLUP");
  }
  Serial.println();
  pinMode(LED_BUILTIN,OUTPUT);
}  

void loop() {
  readKeys();
  delay(100);


}

void readKeys(){
  for (int i { 0 } ; i < cC; i ++ ){
    pinMode (c[i] ,OUTPUT);
    digitalWrite(c[i],LOW);

    for (int j { 0 } ; j < rC; j++ ){
        pinMode(r[j],INPUT_PULLUP);
        while (digitalRead(r[j]) == LOW){
          digitalWrite(LED_BUILTIN, HIGH);
          if (cmdCalled == false){
            Serial.print("Current Row: "); Serial.print(r[j]); Serial.print(" Current Column:  "); Serial.print(c[i]);Serial.println();
            keyboardOut(i,j);
            cmdCalled = true;
          }
        }
        digitalWrite(LED_BUILTIN, LOW);
        cmdCalled = false;
        pinMode(r[j], INPUT);
    }
    
    pinMode(c[i],INPUT);
  }
    
}


void keyboardOut(int rl, int cl) {
  Keyboard.press(ctrlKey);
  Keyboard.press(shiftKey);
  Keyboard.press(altKey);
  Keyboard.press(keys[cl][rl]);
  
  Keyboard.releaseAll();

}
