/*
  Radio Control
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-robot/blob/main/LICENSE
*/

//Setup inputs
const int D0 = 2;
const int D1 = 3;
const int D2 = 4;
const int D3 = 5;

//setup LEDs
const int LED0 = 8;
const int LED1 = 9;
const int LED2 = 10;
const int LED3 = 11;

// setup states to toggle LEDs on radio inputs
int led0State = LOW; // the current state of LED0
int lastD0State; // previous state of D0 input
int currentD0State; // current state of D0 input

int led1State = LOW; // the current state of LED1
int lastD1State; // previous state of D1 input
int currentD1State; // current state of D1 input

int led2State = LOW; // the current state of LED2
int lastD2State; // previous state of D2 input
int currentD2State; // current state of D2 input

int led3State = LOW; // the current state of LED3
int lastD3State; // previous state of D3 input
int currentD3State; // current state of D3 input

void setup() {
  pinMode (D0, INPUT);
  pinMode (D1, INPUT);
  pinMode (D2, INPUT);
  pinMode (D3, INPUT);

  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);

  currentD0State = digitalRead(D0);
  currentD1State = digitalRead(D1);
  currentD2State = digitalRead(D2);
  currentD3State = digitalRead(D3);
}

void loop() {
  //read D0 state and toggle LED0 on state change
  lastD0State    = currentD0State; // save the last state
  currentD0State = digitalRead(D0); // read new state

  if (lastD0State == HIGH && currentD0State == LOW) {

    // toggle state of LED0
    led0State = !led0State;

    // control LED0 according to the toggled state
    digitalWrite(LED0, led0State);
  }

  //read D1 state and toggle LED1 on state change
  lastD1State    = currentD1State; // save the last state
  currentD1State = digitalRead(D1); // read new state

  if (lastD1State == HIGH && currentD1State == LOW) {

    // toggle state of LED1
    led1State = !led1State;

    // control LED1 according to the toggled state
    digitalWrite(LED1, led1State);
  }

  //read D2 state and toggle LED2 on state change
  lastD2State    = currentD2State; // save the last state
  currentD2State = digitalRead(D2); // read new state

  if (lastD2State == HIGH && currentD2State == LOW) {

    // toggle state of LED2
    led2State = !led2State;

    // control LED2 according to the toggled state
    digitalWrite(LED2, led2State);
  }

  //read D3 state and toggle LED3 on state change
  lastD3State    = currentD3State; // save the last state
  currentD3State = digitalRead(D3); // read new state

  if (lastD3State == HIGH && currentD3State == LOW) {

    // toggle state of LED3
    led3State = !led3State;

    // control LED3 according to the toggled state
    digitalWrite(LED3, led3State);
  }
}
