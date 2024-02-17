#include "LedControl.h"
LedControl lc=LedControl(12,10,11,1);

unsigned long delaytime1=500;
unsigned long delaytime2=50;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the two-dimensional array on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int cur_posx = 3;
int cur_posy = 0;
int next_posx = 3;
int next_posy = 0;

//0 = false
// N, W, S, E
int maze[8][8][4] = {
  {{0,0,1,1}, {0,1,0,1}, {0,1,0,1}, {0,1,1,1}, {0,1,0,1}, {0,1,0,1}, {0,1,1,1},{0,1,1,0}},
  {{1,0,1,1}, {0,1,1,1}, {0,1,1,1}, {1,1,0,1}, {0,1,0,1}, {0,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,0,1}, {1,1,0,1}, {0,1,1,1}, {0,1,0,1}, {1,1,0,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,0,1}, {0,1,0,1}, {0,1,1,1}, {1,1,1,1}, {0,1,1,1}, {0,1,1,1}, {1,1,1,1},{1,1,0,0}},
  {{0,0,1,1}, {0,1,1,1}, {1,1,0,1}, {1,1,0,1}, {1,1,1,1}, {1,1,1,1}, {1,1,0,1},{0,1,1,0}},
  {{1,0,1,1}, {1,1,0,1}, {0,1,1,1}, {0,1,0,1}, {1,1,0,1}, {1,1,0,1}, {0,1,0,1},{1,1,1,0}},
  {{1,0,1,1}, {0,1,1,1}, {1,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,1,1},{1,1,1,0}},
  {{1,0,0,1}, {1,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {1,1,0,1},{1,1,0,0}}
};

void setup() {
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  Serial.begin(9600);
}

void brian(){
  // with wires at left, (0,0) is top left.
  lc.setLed(0, cur_posy, cur_posx, true);

  char customKey = customKeypad.getKey();
  
  if (customKey == '2' && maze[cur_posy][cur_posx][0]){ // North
    next_posy = cur_posy - 1;
    Serial.println(customKey);
  } else if (customKey == '8' && maze[cur_posy][cur_posx][2]){ // South
    next_posy = cur_posy + 1;
  } else if (customKey == '6' && maze[cur_posy][cur_posx][3]){ // East
    next_posx = cur_posx + 1;
  } else if (customKey == '4' && maze[cur_posy][cur_posx][1]){ // West
    next_posx = cur_posx - 1;
  } else if (customKey == '2' || customKey == '8' || customKey == '6' || customKey == '4'){
    next_posx = 3;
    next_posy = 0;
  }

  lc.setLed(0, cur_posy, cur_posx, false);
  cur_posx = next_posx;
  cur_posy = next_posy;
}

void loop() { 
  brian();
}
