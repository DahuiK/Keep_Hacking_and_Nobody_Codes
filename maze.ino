#include "LedControl.h"
LedControl lc=LedControl(12,10,11,1);
unsigned long delaytime1=500;
unsigned long delaytime2=50;

int cur_posx = 0;
int cur_posy = 0;
int next_posx = 0;
int next_posy = 0;

//0 = false
// N, W, S, E
int maze[8][8][4] = {
  {{0,0,1,1}, {0,1,1,1}, {0,1,1,1}, {0,1,1,1}, {0,1,1,1}, {0,1,1,1}, {0,1,1,1},{0,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,0}},
  {{1,0,0,1}, {1,1,0,1}, {1,1,0,1}, {1,1,0,1}, {1,1,0,1}, {1,1,0,1}, {1,1,0,1},{1,1,0,0}}
};

const int buttonN = 7;
const int buttonW = 6;
const int buttonS = 5;
const int buttonE = 4;
int stateN = 1;
int stateW = 1;
int stateS = 1;
int stateE = 1;
int lastN = 1;
int lastW = 1;
int lastS = 1;
int lastE = 1;

void setup() {
  // Maze 4 button stuff
  pinMode(buttonN, INPUT);
  pinMode(buttonW, INPUT);
  pinMode(buttonS, INPUT);
  pinMode(buttonE, INPUT);

  // 8x8 display stuff
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  // Serial initialize
  Serial.begin(9600);
}

void loop() {
  // With wires at left, (0,0) is top left.
  lc.setLed(0, cur_posy, cur_posx, true);

  stateN = digitalRead(buttonN);
  stateW = digitalRead(buttonW);
  stateS = digitalRead(buttonS);
  stateE = digitalRead(buttonE);

  // if(stateN){ // North
  //   delay(100);
  //   stateN = digitalRead(buttonN);
  //   if(!stateN){
  //     if(maze[cur_posy][cur_posx][0]){
  //       next_posy = cur_posy - 1;
  //     } else{
  //       next_posx = 0;
  //       next_posy = 0;
  //     }
  //   }
  // }

  // if(stateW){ // West
  //   delay(100);
  //   stateW = digitalRead(buttonW);
  //   if(!stateW){
  //     if(maze[cur_posy][cur_posx][1]){
  //       next_posx = cur_posx - 1;
  //     } else{
  //       next_posx = 0;
  //       next_posy = 0;
  //     }
  //   }
  // }

  // if(stateS){ // South
  //   delay(100);
  //   stateS = digitalRead(buttonS);
  //   if(!stateS){
  //     if(maze[cur_posy][cur_posx][2]){
  //       next_posy = cur_posy + 1;
  //     } else{
  //       next_posx = 0;
  //       next_posy = 0;
  //     }
  //   }
  // }
  
  // if(stateE){ // East
  //   delay(100);
  //   stateE = digitalRead(buttonE);
  //   if(!stateE){
  //     if(maze[cur_posy][cur_posx][3]){
  //       next_posx = cur_posx + 1;
  //     } else{
  //       next_posx = 0;
  //       next_posy = 0;
  //     }
  //   }
  // }

  if(!stateN && stateN != lastN){ // North
      if(maze[cur_posy][cur_posx][0]){
        next_posy = cur_posy - 1;
      } else{
        next_posx = 0;
        next_posy = 0;
      }
  }

  if(!stateW && stateW != lastW){ // West
      if(maze[cur_posy][cur_posx][1]){
        next_posx = cur_posx - 1;
      } else{
        next_posx = 0;
        next_posy = 0;
      }
  }

  if(!stateS && stateS != lastS){ // South
      if(maze[cur_posy][cur_posx][2]){
        next_posy = cur_posy + 1;
      } else{
        next_posx = 0;
        next_posy = 0;
      }
  }

  if(!stateE && stateE != lastE){ // East
      if(maze[cur_posy][cur_posx][3]){
        next_posx = cur_posx + 1;
      } else{
        next_posx = 0;
        next_posy = 0;
      }
  }

  lastN = stateN;
  lastW = stateW;
  lastS = stateS;
  lastE = stateE;

  delay(100);

  if(cur_posx != next_posx || cur_posy != next_posy){
    lc.setLed(0, cur_posy, cur_posx, false);
    cur_posx = next_posx;
    cur_posy = next_posy;
  }
  
  Serial.print(stateN);
  Serial.print(" ");
  Serial.print(stateW);
  Serial.print(" ");
  Serial.print(stateS);
  Serial.print(" ");
  Serial.println(stateE);
}
