#include "My_SegmentDisplay.h"

My_SegmentDisplay::My_SegmentDisplay(int numDisplays) {
  _numDisplays = numDisplays;
  _segPins = new int[7];
  _displayPins = new int[_numDisplays];
  _digitValues = new int[_numDisplays];
  _dots = new bool[_numDisplays];  // Initialize the dot control array
  _colonPin = -1;
  _dotPin = -1;  // Initialize dot pin
  _lastUpdate = 0;
  _updateInterval = 5; // Multiplexing interval in ms

  // Initialize colon blink timing
  _colonOnDuration = 500;  // Default colon on duration
  _colonOffDuration = 500; // Default colon off duration
  _lastColonUpdate = 0;
}

My_SegmentDisplay::~My_SegmentDisplay() {
  delete[] _segPins;
  delete[] _displayPins;
  delete[] _digitValues;
  delete[] _dots;  // Free the dot array
}

void My_SegmentDisplay::setPins(const int segPins[], const int displayPins[], int colonPin, int dotPin) {
  // Set pins for segments
  for (int i = 0; i < 7; i++) {
    _segPins[i] = segPins[i];
    pinMode(_segPins[i], OUTPUT);
  }

  // Set pins for individual displays
  for (int i = 0; i < _numDisplays; i++) {
    _displayPins[i] = displayPins[i];
    pinMode(_displayPins[i], OUTPUT);
    _dots[i] = false; // Initialize all dots to be off
  }

  // Set colon pin if provided
  if (colonPin != -1) {
    _colonPin = colonPin;
    pinMode(_colonPin, OUTPUT);
  }

  // Set dot pin if provided
  if (dotPin != -1) {
    _dotPin = dotPin;
    pinMode(_dotPin, OUTPUT);
  }
}

void My_SegmentDisplay::show(int displayIndex, int value) {
  // Display value on a specific display
  if (displayIndex >= 0 && displayIndex < _numDisplays) {
    _digitValues[displayIndex] = value;
  }
}

void My_SegmentDisplay::update() {
  unsigned long currentMillis = millis();

  // Check if it's time to update the multiplexing
  if (currentMillis - _lastUpdate >= _updateInterval) {
    static int currentDisplay = 0;

    // Turn off all displays
    for (int i = 0; i < _numDisplays; i++) {
      digitalWrite(_displayPins[i], LOW);
    }

    // Turn on the current display
    digitalWrite(_displayPins[currentDisplay], HIGH);
    
    // Display the digit on the current display
    displayDigit(_digitValues[currentDisplay], currentDisplay);

    // Update the colon (:) blink
    if (_colonPin != -1) {
      if (currentMillis - _lastColonUpdate >= (_colonOnDuration + _colonOffDuration)) {
        _lastColonUpdate = currentMillis;
        setColon(!_lastColonUpdate);  // Toggle colon state
      }
    }

    // Move to the next display
    currentDisplay++;
    if (currentDisplay >= _numDisplays) {
      currentDisplay = 0;
    }

    _lastUpdate = currentMillis;
  }
}

void My_SegmentDisplay::setColonBlinkDuration(unsigned long onDuration, unsigned long offDuration) {
  _colonOnDuration = onDuration;
  _colonOffDuration = offDuration;
}

void My_SegmentDisplay::setColon(bool state) {
  digitalWrite(_colonPin, state ? HIGH : LOW);
}

void My_SegmentDisplay::setDot(int displayIndex, bool state) {
  // Control the decimal point (.) for the specific display using its own dot pin
  if (_dotPin != -1) {
    digitalWrite(_dotPin, state ? HIGH : LOW);  // Dot is on/off for the whole display
  }
  
  // Set the dot state for the specific display (only if dot exists)
  if (displayIndex >= 0 && displayIndex < _numDisplays) {
    _dots[displayIndex] = state;
  }
}

void My_SegmentDisplay::displayDigit(int digit, int displayIndex) {
  byte segments = digitCodes[digit];

  // If the dot is on for this display, set the appropriate bit in the segment code
  if (_dots[displayIndex]) {
    segments |= B10000000;  // Set the 8th bit for the dot
  }

  for (int i = 0; i < 7; i++) {
    digitalWrite(_segPins[i], (segments >> i) & 1);
  }
}
