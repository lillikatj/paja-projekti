#include "AccelStepper.h"  
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:  

#define dirPin 2  
#define stepPin 3  
#define motorInterfaceType 1  

const int stepsPerRev = 3200; 

//Button constants: 

const int buttonPin = 7; 
int buttonState = 0; 
int buttonPresses = 1; 

// Create a new instance of the AccelStepper class:  

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);  

// target amount of steps

long targetSteps = 3 * stepsPerRev; 

   
void setup() {  
  // Set the maximum speed in steps per second:  
  stepper.setMaxSpeed(1000); 
  stepper.setAcceleration(500); 

  // Button setup:  
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600); 
} 

  

void loop() {  
  buttonState = digitalRead(buttonPin); 

  if (buttonState == LOW) { 
    Serial.println(buttonPresses); 

    if (stepper.distanceToGo() == 0){ 
      if (buttonPresses % 2 == 0){ 
        stepper.moveTo(stepper.currentPosition() + targetSteps); 
        buttonPresses++; 
      } else { 
        stepper.moveTo(stepper.currentPosition() - targetSteps); 
        buttonPresses++; 
      } 
    } 
  } 
  stepper.run(); 
} 
