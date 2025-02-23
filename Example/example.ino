#include <My_SegmentDisplay.h>

// Pins for segments A-G (Adjust these to match your wiring)
const int segPins[] = {2, 3, 4, 5, 6, 7, 8};

// Pins for individual displays (Adjust these to match your wiring)
const int displayPins[] = {9, 10, 11, 12};

// Pin for the colon
const int colonPin = 13;

// Pin for the decimal dot
const int dotPin = 14;

// Create the display object with 4 digits
My_SegmentDisplay display(4);

void setup() {
  // Set pins for segments, displays, colon, and decimal dot
  display.setPins(segPins, displayPins, colonPin, dotPin);

  // Display numbers on each of the 4 displays
  display.show(0, 1);  // First display shows '1'
  display.show(1, 2);  // Second display shows '2'
  display.show(2, 3);  // Third display shows '3'
  display.show(3, 4);  // Fourth display shows '4'

  // Set the colon blink duration (500ms on, 500ms off)
  display.setColonBlinkDuration(500, 500);

  // Enable the decimal point (dot) on the first display
  display.setDot(0, true);  // First display gets a decimal point
}

void loop() {
  // Update the display (handle multiplexing and blink timing)
  display.update();

  // After 3 seconds, turn off the decimal dot on the first display
  delay(3000);
  display.setDot(0, false);  // Turn off the dot
  delay(1000);  // Wait for 1 second before continuing
}
