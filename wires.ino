const int ledPins[] = {0, 2, 4, 6, 8};
const int pullPins[] = {1, 3, 5, 7, 9};
const int wrongPin = 2;

const int gameVersion[] = {A0, A1};

bool correctOrder = true;
long randNumber;
int desiredOrder[5];
int cdesiredOrder[5];

void setup() {
    for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
    for (int i = 0; i < 5; i++) {
    pinMode(pullPins[i], INPUT);
  }
    for (int i = 0; i < 2; i++) {
    pinMode(gameVersion[i], OUTPUT);
  }
  Serial.begin(9600);
  // randomSeed(analogRead(0));
  // randNumber = random(0, 3);
  randNumber = 2;
  Serial.println(randNumber);
  
  if (randNumber == 0){
  desiredOrder[0] = pullPins[2];
  desiredOrder[1] = pullPins[0];
  desiredOrder[2] = pullPins[4];
  desiredOrder[3] = pullPins[3];
  desiredOrder[4] = pullPins[1];
  
  cdesiredOrder[0] = ledPins[2];
  cdesiredOrder[1] = ledPins[0];
  cdesiredOrder[2] = ledPins[4];
  cdesiredOrder[3] = ledPins[3];
  cdesiredOrder[4] = ledPins[1];
  }
    
  if (randNumber == 1){
  desiredOrder[0] = pullPins[0];
  desiredOrder[1] = pullPins[4];
  desiredOrder[2] = pullPins[2];
  desiredOrder[3] = pullPins[3];
  desiredOrder[4] = pullPins[1];
  
  cdesiredOrder[0] = ledPins[0];
  cdesiredOrder[1] = ledPins[4];
  cdesiredOrder[2] = ledPins[2];
  cdesiredOrder[3] = ledPins[3];
  cdesiredOrder[4] = ledPins[1];
  }
    
  if (randNumber == 2){
  desiredOrder[0] = pullPins[3];
  desiredOrder[1] = pullPins[1];
  desiredOrder[2] = pullPins[4];
  desiredOrder[3] = pullPins[2];
  desiredOrder[4] = pullPins[0];
  
  cdesiredOrder[0] = ledPins[3];
  cdesiredOrder[1] = ledPins[1];
  cdesiredOrder[2] = ledPins[4];
  cdesiredOrder[3] = ledPins[2];
  cdesiredOrder[4] = ledPins[0];
  }
}

void loop() {
     for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  
  if(randNumber == 0){
  digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  }
    if(randNumber == 1){
  digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
  }
    if(randNumber == 2){
  digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }
  
  int currentPin = -1;
    if (!correctOrder) {
    for (int i = 0; i < 5; i++) {
      //delay(100);
      digitalWrite(cdesiredOrder[i], LOW);
    }
  }

  if(correctOrder){
  for (int i = 0; i < 5; i++) {
    if (digitalRead(desiredOrder[i]) == LOW) {
      digitalWrite(cdesiredOrder[i], HIGH);
      currentPin = i;
    } else {
      digitalWrite(cdesiredOrder[i], LOW);
    }
  }
  }

  if (currentPin > 0) {
    for (int j = 0; j < currentPin; j++) {
      if (digitalRead(desiredOrder[j]) != LOW) {
        correctOrder = false;
        break;
      }
    }
  digitalWrite(wrongPin, correctOrder ? LOW : HIGH);
}
}
