#ifndef MY_SEGMENT_DISPLAY_H
#define MY_SEGMENT_DISPLAY_H

#include <Arduino.h>

class My_SegmentDisplay {
  public:
    // Number of displays
    My_SegmentDisplay(int numDisplays);
    ~My_SegmentDisplay();

    // Set the pins for segments, displays, and optional colon and dot pins
    void setPins(const int segPins[], const int displayPins[], int colonPin = -1, int dotPin = -1);

    // Display number on a specific display
    void show(int displayIndex, int value);

    // Update the displays
    void update();

    // Control colon (:) blink duration
    void setColonBlinkDuration(unsigned long onDuration, unsigned long offDuration);
    void setColon(bool state);

    // Control the decimal dot (.) for individual displays (continuous dot)
    void setDot(int displayIndex, bool state);

  private:
    // Number of displays
    int _numDisplays;

    // Pins for segments and displays
    int* _segPins;
    int* _displayPins;
    int _colonPin;
    int _dotPin;  // Pin for controlling the decimal dot

    // Values to display on the displays
    int* _digitValues;
    bool* _dots;  // Array to control the dots (decimal points) on each display

    // Multiplexing interval time
    unsigned long _lastUpdate;
    unsigned long _updateInterval;

    // Colon blink timing
    unsigned long _colonOnDuration;
    unsigned long _colonOffDuration;
    unsigned long _lastColonUpdate;

    // Segment codes for 0-9 (no decimal point)
    const byte digitCodes[10] = {
      B1111110, // 0
      B0110000, // 1
      B1101101, // 2
      B1111001, // 3
      B0110011, // 4
      B1011011, // 5
      B1011111, // 6
      B1110000, // 7
      B1111111, // 8
      B1111011  // 9
    };

    // Function to display a digit on the segment display
    void displayDigit(int digit, int displayIndex);
};

#endif
