bool buttonDone = false;
bool wiresDone = false;
bool leakDone = false;
bool mazeDone = false;

const int strikePins[] = {23, 25, 27};
int strikes = 0;

const int buzzerPin = 53;


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
  Serial.begin(9600);
}

void loop(){ // main code loop
  // if(buttonDone && wiresDone && leakDone && mazeDone){ //If all the modules are complete, call the game won function
  //   gamewon();
  // }

  if(mazeDone){ //If all the modules are complete, call the game won function
    gamewon();
  }

  // strike();
  // delay(1000);

  if(!buttonDone){

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

  if(strikes >= 3){
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


