#include <Servo.h> // servo library

const int buttonPin = 2;  // pushbutton 1 pin
const int ledPin =  13;    // LED pin
const int servoPin = 9;    // servo pin (hopefully)

// servo control object
Servo servo1;

// counter for button presses
short buttonPresses = 0;
// var for if has been programmed
bool programmed = false;
// var for if has been run
bool hasRun = false;


// put your setup code here, to run once:
void setup() {
  // Set up the pushbutton pins to be an input:
  pinMode(buttonPin, INPUT);
  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);
  // attach servo!!
  servo1.attach(9);
}

void loop() {
  int buttonState;  // variables to hold the pushbutton states
  buttonState = digitalRead(buttonPin);

  // if button is being pressed
  if (buttonState == LOW){

    hasRun = false;
    digitalWrite(ledPin, HIGH);
    buttonPresses += 1;
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);

    programmed = true;

  } // end "if (buttonState == LOW)"
  // if button is not being pushed
  else if (buttonState == HIGH){
    // reset servo arm position
    servo1.write(0);
    if (!hasRun){
      digitalWrite(ledPin, LOW);
      // delay to give below time to run
      delay(3000);
      if (programmed && (buttonState != LOW)){
        // blink once for each buttonPress
        for(short n = 0; n < buttonPresses; n += 1){
          digitalWrite(ledPin, HIGH);
          delay(250);
          digitalWrite(ledPin, LOW);
          delay(250);       
        }

        // milliseconds * seconds/min * min/hour * hours (hours is buttonPresses)
        delay(1000UL*60*60*buttonPresses);
        
        // move the arm 180* back, then pull from 90* back to 180* three times
        for (int i=1; i <= 3; i +=1){
          for(int position = 0; position <= 225; position += 2){
                servo1.write(position);
                delay(10);  
          }
        }
        hasRun = true;
      }

    }
    else if(hasRun){
      digitalWrite(ledPin, LOW);
      delay(4000);
      digitalWrite(ledPin, HIGH);
      delay(1000);
    }    
  }//end else if (buttonState == HIGH)

}
