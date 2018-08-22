int green = 8;
int yellow = 7;
int blue = 4;
int timerer = 12;
int beepboop = 8;

int ledStateGreen = LOW;
int ledStateBlue = LOW;
long previousMillis = 0;
long interval;

int buttonPin = 2;
int buttonState = 1;
bool pressed = 0;
long pressTime = 0;

int phase = 0;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(timerer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
}

void loop() {
  digitalWrite(timerer, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(timerer, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  // update current time and state of button
  unsigned long currentMillis = millis();
  int buttonState = digitalRead(buttonPin);

  // measure time since last button press
  long progress = currentMillis - previousMillis;

  // check to see if button has been pressed
  // over 2 seconds since last press
  // (to prevent multiple presses registering)
  if ((pressTime - currentMillis) > 2000){
    if(buttonState == 0){
      pressed = 1;
      pressTime = currentMillis;}
    else{
      pressed = 0;}
  }

  // phase 0 is "work" phase
  // if button has been pressed, add 2 minutes to work timer
  if (phase == 0){

    if (pressed == 1){
      interval = 1620000;}

    // if interval is over, record current
    // time for measuring next interval
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;

    // set green and blue LED states
    if (ledStateGreen == LOW){
      ledStateGreen = HIGH;
      ledStateBlue = LOW;}
    else {
      ledStateGreen = LOW;}

    // apply LED states to LEDs
    // reset interval and switch to "break" phase
    digitalWrite(green, ledStateGreen);
    digitalWrite(blue, ledStateBlue);
    interval = 1500000;
    buttonState = 1;
    phase = 1;
    }
  }

  else {

  // if button has been pressed, add 2 minutes to break timer
  if (pressed == 1){
    interval = 420000;}

      // if interval is over, record current
      // time for measuring next interval
      if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;

      // set blue and green LED states
      if (ledStateBlue == HIGH){;
        ledStateBlue = LOW; }
      else {
        ledStateBlue = HIGH;
        ledStateGreen = LOW;}

    // apply LED states to LEDs
    // reset interval and set to "work" phase
    digitalWrite(green, ledStateGreen);
    digitalWrite(blue, ledStateBlue);
    interval = 300000;
    buttonState = 1;
    phase = 0;
    }
  }

  // calculate time left in interval
  unsigned long timeLeft = (interval - progress);

  // if there are less than two minutes left, light up yellow LED
  if (timeLeft < 120000) {
    digitalWrite(yellow, HIGH); }
  else {
    digitalWrite(yellow, LOW); }

  // reset pressed variable
  pressed = 0;
}
