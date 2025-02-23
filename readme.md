# My_SegmentDisplay Library

`My_SegmentDisplay` is an Arduino library for controlling multiplexed 7-segment displays. It allows you to manage multiple displays with the option of adding a colon and decimal dot for advanced formatting. The library supports customizable blink durations for the colon and the ability to display individual dots on specific digits.

## Features
- Support for multiplexed 7-segment displays (1 to 10 displays).
- Option to control the colon (:) with customizable blink durations.
- Control decimal dots on individual displays (dot per display).
- Non-blocking code for smooth multiplexing and timing control.

## Installation
1. Download the library files `My_SegmentDisplay.h` and `My_SegmentDisplay.cpp`.
2. Place these files in the `libraries` folder of your Arduino project directory.
3. In the Arduino IDE, navigate to **Sketch > Include Library > My_SegmentDisplay** to include the library in your project.

## Usage

### Initialization
```cpp
#include <My_SegmentDisplay.h>

// Pin configuration for the segments (A-G)
const int segPins[] = {2, 3, 4, 5, 6, 7, 8};

// Pin configuration for each of the 7-segment displays
const int displayPins[] = {9, 10, 11, 12};

// Pin for the colon (optional)
const int colonPin = 13;

// Pin for the decimal dot (optional)
const int dotPin = 14;

// Create a My_SegmentDisplay object for 4 displays
My_SegmentDisplay display(4);

void setup() {
  // Set the pins for segments, displays, colon, and decimal dot
  display.setPins(segPins, displayPins, colonPin, dotPin);

  // Display values on the individual 4 displays
  display.show(0, 1);  // First display shows '1'
  display.show(1, 2);  // Second display shows '2'
  display.show(2, 3);  // Third display shows '3'
  display.show(3, 4);  // Fourth display shows '4'

  // Set the colon blink duration (500ms on, 500ms off)
  display.setColonBlinkDuration(500, 500);

  // Enable the decimal dot on the first display
  display.setDot(0, true);  // First display gets a decimal point
}

void loop() {
  // Update the display and manage multiplexing and blinking
  display.update();

  // Turn off the decimal dot on the first display after 3 seconds
  delay(3000);
  display.setDot(0, false);
  delay(1000);
}
