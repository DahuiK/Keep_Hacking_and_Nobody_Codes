bool buttonDone = false;
bool wiresDone = false;
bool leakDone = false;
bool mazeDone = false;

const int strikePins[] = {23, 25, 27};
int strikes = 0;

const int buzzerPin = 53;

//THE BUTTON STUFF
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int ran; 
int interval = 10000; 
int currentbutton = 0; 
int previousbutton = 1; 
int buttoncount = 0;
int initbutton = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long pressedMillis = 0;
bool firstpress = true;
bool buttonPressed = false;


const int buttonPin = 35; //change the pinnumber later 
int redPin = 29; 
int greenPin = 31; 
int bluePin = 33; 
bool buttonStart = false;


// MAZE STUFF
#include "LedControl.h"
LedControl lc=LedControl(12,10,11,1);
unsigned long delaytime1=500;
unsigned long delaytime2=50;
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int cur_posx = 3;
int cur_posy = 0;
int next_posx = 3;
int next_posy = 0;
int maze[8][8][4] = {
  {{0,0,1,1}, {0,1,0,1}, {0,1,0,0}, {0,0,1,1}, {0,1,0,1}, {0,1,0,1}, {0,1,1,1},{0,1,1,0}},
  {{1,0,1,1}, {0,1,1,0}, {0,0,1,1}, {1,1,0,0}, {0,0,0,1}, {0,1,1,0}, {1,0,1,0},{1,0,1,0}},
  {{1,0,1,0}, {1,0,0,1}, {1,1,0,0}, {0,0,1,1}, {0,1,0,1}, {1,1,0,0}, {1,0,1,0},{1,0,1,0}},
  {{1,0,0,1}, {0,1,0,1}, {0,1,1,0}, {1,0,1,0}, {0,0,1,1}, {0,1,1,0}, {1,0,1,0},{1,0,0,0}},
  {{0,0,1,0}, {0,0,1,1}, {1,1,0,1}, {1,1,0,0}, {1,0,1,0}, {1,0,1,0}, {1,0,0,1},{0,1,1,0}},
  {{1,0,1,1}, {1,1,0,0}, {0,0,1,1}, {0,1,0,1}, {1,1,0,0}, {1,0,0,1}, {0,1,0,1},{1,1,1,0}},
  {{1,0,1,0}, {0,0,1,0}, {1,0,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,1,0},{1,0,1,0}},
  {{1,0,0,1}, {1,1,0,1}, {0,1,0,1}, {0,1,0,0}, {0,0,0,1}, {0,1,0,1}, {1,1,0,0},{1,0,0,0}}
};



void setup(){ // initializing and set up variables
  for(int i = 0; i < 3; i++){ // setting the strike leds to off
    pinMode(strikePins[i], OUTPUT);
    digitalWrite(strikePins[i], LOW);
  }

  pinMode(buzzerPin, OUTPUT); // buzzer pin set as output


  //MAZE STUFF
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  // Serial.begin(9600);

  //BUTTON STUFF 
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("BUTTON...");
  display.display(); 

  pinMode(redPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT);
  randomSeed(analogRead(0));
  ran = 0;
}

void loop(){ // main code loop 
  
  // if(buttonDone && wiresDone && leakDone && mazeDone){ //If all the modules are complete, call the game won function
  //   gamewon();
  // }

  if(buttonDone && mazeDone){ //If all the modules are complete, call the game won function
    gamewon();
  }
  
  // strike();
  // delay(1000);

  if(!buttonDone){
    buttoncheck();
  }

  if(!wiresDone){

  }

  if(!leakDone){

  }

  if(!mazeDone){
    mazegame();
  }
}

void strike(){
  strikes++;
  digitalWrite(strikePins[strikes - 1], HIGH);
  digitalWrite(buzzerPin, 255);
  delay(500);
  digitalWrite(buzzerPin, 0);

  if(strikes == 3){
    lose();
  }
}

void gamewon(){
  while(true){
    for(int i = 0; i < 3; i++){
      digitalWrite(strikePins[i], HIGH);
    }
    delay(500);
    for(int i = 0; i < 3; i++){ // setting the strike leds to off
      digitalWrite(strikePins[i], LOW);
    }
    delay(500);
  }
}

void lose(){
  digitalWrite(buzzerPin, 255);
  delay(3000);
  digitalWrite(buzzerPin, 0);
  // BOMB SFX
  // for(int i = 512; i > 1; i /= 2){
  //   digitalWrite(buzzerPin, 255);
  //   delay(100);
  //   digitalWrite(buzzerPin, 0);
  //   delay(i);
  // }
  // digitalWrite(buzzerPin, 255);
  // delay(2000);
  // digitalWrite(buzzerPin, 0);
}

void buttoncheck(){
  if(buttonStart){
    buttongame();
  }

  currentbutton = digitalRead(buttonPin);
  if (currentbutton == 0) {
    buttonStart = true;
    previousMillis = millis();
  }
}

void buttongame() { 
  // Serial.println(currentbutton); 
  currentMillis = millis();
  // button_ran();
  // delay(500); 
  if (currentMillis - previousMillis <= interval && !buttonDone) {
    // save the last time you blinked the LED

    if (ran == 0) {
      display.println("PRESS");
      display.display(); 
      setColor(255,0,0);
      currentbutton = digitalRead(buttonPin);
      Serial.println(currentbutton);
      if (currentbutton == 0) {
        buttonPressed = true; 
        buttonwin(); 
      } 
    } else if(ran ==1) {
      display.println("HOLD");
      display.display(); 
      setColor(255, 255,0);
      currentbutton = digitalRead(buttonPin);
      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }
      if (currentbutton == 0){
        buttonPressed = true;
        while (currentMillis - pressedMillis > 3000){
          buttonwin();
        }
      } 
    } else if(ran == 2){
      display.println("DETONATE");
      display.display(); 
      setColor(0,0, 255);
      currentbutton = digitalRead(buttonPin);
      if(currentbutton == 0){
        pressedMillis = currentMillis;
        buttonloss();
      }
    } 
    if (ran == 3){
      display.println("SMASH");
      display.display();  
      setColor(255,255,255);
      currentbutton = digitalRead(buttonPin); 

      if (buttoncount > 5){
        buttonwin();
      }

      if(currentbutton){
        currentbutton = digitalRead(buttonPin);
        if(!currentbutton){
          buttoncount++;
        }
      }
    }
  } else if (currentMillis - previousMillis >= interval && !buttonDone) {
    if (ran == 0) {
      display.println("PRESS");
      display.display(); 
      setColor(255,0,0);
      currentbutton = digitalRead(buttonPin);
      if (currentbutton == 1){
        pressedMillis = currentMillis; 
        buttonPressed = false;
        buttonloss();
       }
    } else if(ran ==1) {
      display.println("HOLD");
      display.display(); 
      setColor(255, 255,0);
      currentbutton = digitalRead(buttonPin);
      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }
      if(currentbutton == 1){
        pressedMillis = currentMillis;
        buttonloss();
      }
    } else if(ran == 2){
      display.println("DETONATE");
      display.display(); 
      setColor(0,0, 255);
      currentbutton = digitalRead(buttonPin);
      if(currentbutton == 1){
        pressedMillis = currentMillis;
        buttonwin();
      }
    } 
    if (ran == 3){
      display.println("SMASH");
      display.display();  
      setColor(255,255,255);
      buttonloss();
    }
  }
}

void buttonwin() {
  digitalWrite(redPin, 0); 
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("PASS"); 
  display.display();
  buttonDone = true;
}

void buttonloss(){
  // setColor(0,0,0);
  digitalWrite(redPin, 0); 
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("STRIKE"); 
  display.display(); 
  previousMillis = millis();
  strike();
}


// Button stuff
void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// void button_ran() {
//   if (ran == 5) {
//   initbutton = digitalRead(buttonPin);
//     if(initbutton == 0){
//       ran = 1;
//     } 
//   }
// }


void mazegame(){
  // with wires at left, (0,0) is top left.
  lc.setLed(0, cur_posy, cur_posx, true);

  char customKey = customKeypad.getKey();
  
  if (customKey == '2' && maze[cur_posy][cur_posx][0]){ // North
    next_posy = cur_posy - 1;
  } else if (customKey == '8' && maze[cur_posy][cur_posx][2]){ // South
    next_posy = cur_posy + 1;
  } else if (customKey == '6' && maze[cur_posy][cur_posx][3]){ // East
    next_posx = cur_posx + 1;
  } else if (customKey == '4' && maze[cur_posy][cur_posx][1]){ // West
    next_posx = cur_posx - 1;
  } else if (customKey == '2' || customKey == '8' || customKey == '6' || customKey == '4'){
    strike();
    next_posx = 3;
    next_posy = 0;
  }

  lc.setLed(0, cur_posy, cur_posx, false);
  cur_posx = next_posx;
  cur_posy = next_posy;
  if(cur_posy == 7 && cur_posx == 4){
    for(int i = 0; i <= 7; i++){ // turn on all leds if you finish the maze
      for(int j = 0; j <= 7; j++){
        lc.setLed(0, i, j, true);
      }
    }
    mazeDone = true;
  }
}


