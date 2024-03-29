// pomodoro timer for cytron arduino

// Pomodoro lengths (in ms)
const unsigned long pomolength = 1500000;      // 25 minutes
const unsigned long breaklength = 300000;      //  5 minutes
const unsigned long longbreaklength = 2100000; // 35 minutes

//////////////////////////////////////////////////////////////////////////////
// GPIO assignment                                                          //
const int button = 2;          // button                                    //
const int buttonLED = 3;       // fades while waiting for user button press //
const int buzzer = 8;          // buzzes after every pomo & break           //
const int timeBlinkLED = 13;   // blinks every second                       //
int brightness = 0;            // LED brightness                            //
int fadeAmount = 5;            // how much to fade LED                      //
//                                                                          //
// blinks when pomo session, solid when pomo session over                    //
const int pomo1 = 4;           // 1 - +25m = 25m                            //
const int pomo2 = 5;           // 3 - +25m = 55m                            //
const int pomo3 = 6;           // 5 - +25m = 85m                            //
const int pomo4 = 7;           // 7 - +25m = 115m                           //
//                                                                          //
// blinks when break session, solid when break session over                  //
const int break1 = 9;          // 2 - +5m = 30m                             //
const int break2 = 10;         // 4 - +5m = 60m                             //
const int break3 = 11;         // 6 - +5m = 90m                             //
const int break4 = 12;         // 8 - +35m = 150m (2.5hrs)                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// button states
int buttonState = 0;
int pressed = 1;
long pressTime = 0;

// waiting blinks - blinks only when waiting for action
int ledState = LOW;

// timer
unsigned long previousMillis = 0;
unsigned long interval = 0;

// pomo sequence
int sequence = 0;

// waiting for input
int waitInput = 1;

// function declarations
void blinkOnce(int pinInput);
void fadeBlink(int pinInput);
void solidify(int pinInput);
void unsolidify(int pinInput);
void clearAllLEDs();
void blinkSession(int blinkLED, unsigned long blinkLength);
void waitTone();
int waitingAction(unsigned long currentMillis);

void setup(){
  pinMode(button, INPUT_PULLUP);
  pinMode(buttonLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(timeBlinkLED, OUTPUT);
  pinMode(pomo1, OUTPUT);
  pinMode(pomo2, OUTPUT);
  pinMode(pomo3, OUTPUT);
  pinMode(pomo4, OUTPUT);
  pinMode(break1, OUTPUT);
  pinMode(break2, OUTPUT);
  pinMode(break3, OUTPUT);
  pinMode(break4, OUTPUT);
}

void loop(){

  // blinks when no timers are going on - waiting for button press
  unsigned long currentMillis = millis();
   if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(timeBlinkLED, ledState);
  }

  // forgot why I made this, scared to remove in fear of destroying something
  if(digitalRead(2) == LOW){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }

  // waiting to start || waiting for button press
  if(waitInput == 1){
    waitingAction(currentMillis);
  }

  // timer phase / Pomodoro sequences. Check README.md for more info
  else{
    // Pomodoro 1
    if(sequence == 1){ //1st pomo
      blinkSession(pomo1, pomolength);
      solidify(pomo1);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 2){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 3){
      blinkSession(break1, breaklength);
      solidify(break1);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 4){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }

    // Pomodoro 2
    else if(sequence == 5){
      blinkSession(pomo2, pomolength);
      solidify(pomo2);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 6){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 7){
      blinkSession(break2, breaklength);
      solidify(break2);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 8){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }

    // Pomodoro 3
    else if(sequence == 9){
      blinkSession(pomo3, pomolength);
      solidify(pomo3);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 10){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 11){
      blinkSession(break3, breaklength);
      solidify(break3);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 12){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }

    // Pomodoro 4
    else if(sequence == 13){
      blinkSession(pomo4, pomolength);
      solidify(pomo4);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 14){
      waitingAction(currentMillis);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 15){
      blinkSession(break4, longbreaklength);
      solidify(break4);
      waitInput = 1;
      sequence++;
    }
    else if(sequence == 16){
      sequence = 0;
      waitingAction(currentMillis);
      clearAllLEDs();
      waitInput = 1;
    }

    //else error
    else{
      blinkOnce(3);
      blinkOnce(4);
      blinkOnce(5);
      blinkOnce(6);
      blinkOnce(7);
      blinkOnce(9);
      blinkOnce(10);
      blinkOnce(11);
      blinkOnce(12);
      blinkOnce(13);
    }
  }
}

// self explanatory
void blinkOnce(int pinInput){
  digitalWrite(pinInput, HIGH);
  delay(1000);
  digitalWrite(pinInput, LOW);
  delay(1000);
}

// wanted to add fade to waiting period, but didn't implement. Kept here
// just in case I wanna use it again
void fadeBlink(int pinInput){
  analogWrite(pinInput, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

// switches LED on
void solidify(int pinInput){
  digitalWrite(pinInput, HIGH);
}

// switches LED off
void unsolidify(int pinInput){
  digitalWrite(pinInput, LOW);
}

// clears all LEDs for a new pomodoro
void clearAllLEDs(){
  digitalWrite(pomo1, LOW);
  digitalWrite(pomo2, LOW);
  digitalWrite(pomo3, LOW);
  digitalWrite(pomo4, LOW);
  digitalWrite(break1, LOW);
  digitalWrite(break2, LOW);
  digitalWrite(break3, LOW);
  digitalWrite(break4, LOW);
}

// blinks LED for specified length (blinkLength), used for pomo and break timer
void blinkSession(int blinkLED, unsigned long blinkLength){
  digitalWrite(3, LOW);
  int blinks = 0;
  bool blinkSesh = 1;
  while(blinks < blinkLength){
    digitalWrite(blinkLED, HIGH);
    delay(1000);
    digitalWrite(blinkLED, LOW);
    delay(1000);
    blinks += 2000;
  }
  tone(buzzer, 261, 500);
  delay(500);
  noTone(buzzer);
}

// triggers the buzzer when waiting for input to alert user
void waitTone(){
  tone(buzzer, 261, 500);
  noTone(buzzer);
  delay(500);
  tone(buzzer, 261, 500);
}

// what to do when waiting for button input
int waitingAction(unsigned long currentMillis){
  if ((pressTime - currentMillis) > 5000){
    if(buttonState == 0){
      pressed = 1;
      pressTime = currentMillis;
    }
    else{
      pressed = 0;
    }
  }
  waitTone();
  pressed = digitalRead(button);

  //if button pressed, stop waiting
  if(pressed == 0){
    waitInput = 0;
    sequence++;
    return 1;
  }

  //no button press, keep waiting
  else{
    return 0;
  }
}

