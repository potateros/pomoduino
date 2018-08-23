# pomoduino

:tomato: Pomodoro timer built with Arduino :tomato:

## What is a Pomodoro? :tomato::question: 

The Pomodoro Technique is a time management method that uses a timer to break down work into intervals, traditionally 25 minutes in length, separated by short breaks. See https://en.wikipedia.org/wiki/Pomodoro_Technique for further details.

It is also an Italian dish. Yum! :pizza:

## Components required :electric_plug:

- 1x Arduino Uno + USB & power
- 1x Push button
- 1x Piezo buzzer
- 9x LEDs
- 9x 330 Ohm resistors
- cables, plenty of them

## Pin mapping :world_map:

| Pin | Label        |
| --- | ------------ |
| 2   | Button       |
| 3   | ignore       |
| 4   | LED          |
| 5   | LED          |
| 6   | LED          |
| 7   | LED          |
| 8   | Piezo buzzer |
| 9   | LED          |
| 10  | LED          |
| 11  | LED          |
| 12  | LED          |
| 13  | LED          |

## LED Mapping :bulb:

What does the lights mean? (Depends on your setup, I output every pin to an LED)

| Pin | Label           | Solid    | Blinking               |
| --- | --------------- | -------- | ---------------------- |
| 4   | Pomodoro 1      | Finished | In progress            |
| 5   | Pomodoro 2      | Finished | In progress            |
| 6   | Pomodoro 3      | Finished | In progress            |
| 7   | Pomodoro 4      | Finished | In progress            |
| 9   | Break 1         | Finished | In progress            |
| 10  | Break 2         | Finished | In progress            |
| 11  | Break 3         | Finished | In progress            |
| 12  | Break 4         | Finished | In progress            |
| 13  | Input indicator | -        | Waiting for user input |

## Pomodoro Sequence Numbering

| Sequence | Meaning                                   |
| -------- | ----------------------------------------- |
| 0        | Initial start - waiting for input         |
| 1        | 1st pomo in progress                      |
| 2        | 1st pomo end, waiting to start break      |
| 3        | 1st break in progress                     |
| 4        | 1st break end, waiting to start next pomo |
| 5-8      | 2nd set                                   |
| 9-12     | 3rd set                                   |
| 13-16    | 4th set, 16 = long break                  |

## How to use :thinking:

1. Switch on the Arduino. 13 will blink, along with buzzer beeps.

1. Press button to start timer.

1. Either pin 4,5,6,7,9,10,11,12 will blink. The blinking one indicates which part of the pomodoro you are at.

   (Eg. Pin 5 is flashing indicates that you are in your 2nd pomodoro of the session.)

1. Pomodoro pins and/or Break pins will become solid. When that happens, the respective pomodoro session has ended.

   (Eg. Pins 4,5,9,10 is solid. That means you have finished the 1st and 2nd Pomodoros and the 1st and 2nd breaks)

1. When the whole Pomodoro is finished (4 pomodoros, 3 breaks + 1 long break), LEDs will flash sequentially. To start a new Pomodoro session, reset the board.

## FAQs :question:

1. _Nice._

   Thanks

2. _I hit an issue! How do I get help?_

   You can submit an issue, and I'll see what I can do.

3. _Your version is lame. I want to make a cooler version_

   Please do! If you managed to complete it, give me a mention on Twitter @potateros - I'd love to see your creation!

## To-do :spiral_notepad:

(someday)

- Create a 3D printed case for it
- Draw out the schematics
- Images of the breadboard?
- OLED version - more detailed and easier to decipher at a glance
- Written guide?

## Anyways :cool:

I hope you like what I made, feel free to fork and modify to make more awesome versions out of this! :boom:
