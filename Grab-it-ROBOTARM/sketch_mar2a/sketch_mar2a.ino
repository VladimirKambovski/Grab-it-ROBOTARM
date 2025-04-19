#include <Servo.h>

const int clawPin = 3;
const int clawRotationPin = 5;
const int clawUpdownPin = 6;
const int middleElbowPin = 9;
const int bottomElbowPin = 10;
const int baseRotationPin = 11;

Servo claw;
Servo clawRotation;
Servo clawUpdown;
Servo middleElbow;
Servo bottomElbow;
Servo baseRotation;

int clawPos = 140;        
int clawRotationPos = 90;  
int clawUpdownPos = 45;    
int middleElbowPos = 90;   
int bottomElbowPos = 90;   
int baseRotationPos = 90;  

void smoothMove(int &currentPos, int targetChange, int minLimit, int maxLimit, int stepSize) {
  int newPos = constrain(currentPos + targetChange * stepSize, minLimit, maxLimit);
  if (newPos != currentPos) {
    int step = (newPos > currentPos) ? 1 : -1;
    for (int i = currentPos; i != newPos; i += step) {
      currentPos = i;
      delay(5);  
    }
  }
}

void setup() {
  Serial.begin(115200);
  claw.attach(clawPin);
  clawRotation.attach(clawRotationPin);
  clawUpdown.attach(clawUpdownPin);
  middleElbow.attach(middleElbowPin);
  bottomElbow.attach(bottomElbowPin);
  baseRotation.attach(baseRotationPin);
}

void loop() {
  if (Serial.available() > 0) {
    String inputData = Serial.readStringUntil('\n');  
    int values[7]; 
    int index = 0;
    int lastIndex = 0;

    for (int i = 0; i < 7; i++) {
      int nextIndex = inputData.indexOf(',', lastIndex);
      if (nextIndex == -1) nextIndex = inputData.length();
      values[i] = inputData.substring(lastIndex, nextIndex).toInt();
      lastIndex = nextIndex + 1;
    }

    int clawRotationVal = values[0];
    int clawUpDownVal = values[1];
    int clawChange = values[2];
    int baseRotationVal = values[3];
    int bottomElbowVal = values[4];
    int middleElbowVal = values[5];

    smoothMove(clawRotationPos, clawRotationVal, 0, 180, 2);
    smoothMove(clawUpdownPos, clawUpDownVal, 0, 90, 2);
    smoothMove(baseRotationPos, baseRotationVal, 0, 180, 2);
    smoothMove(bottomElbowPos, bottomElbowVal, 0, 180, 1);
    smoothMove(middleElbowPos, middleElbowVal, 0, 180, 1);
    smoothMove(clawPos, clawChange, 80, 180, 2);


    clawRotation.write(clawRotationPos);
    clawUpdown.write(clawUpdownPos);
    baseRotation.write(baseRotationPos);
    bottomElbow.write(bottomElbowPos);
    middleElbow.write(middleElbowPos);
    claw.write(clawPos);
  }
}
