#include <Arduino.h>

// --- Pins ---
const int select_pins[3] = {2, 3, 4};
const int read_pin = 5; 


// --- Function Declarations ---
uint8_t read_multiplexer(const int select_pins[3], int read_pin);


// --- Main ---
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(select_pins[i], OUTPUT);
  }

  pinMode(read_pin, INPUT_PULLUP);
}

void loop() {

  uint8_t readings = read_multiplexer(select_pins, read_pin);

  for (int i = 0; i < 8; ++i) {

    if ((readings >> i) & ~0) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    Serial.print(" ");
  }
  Serial.println();

  delay(1000);
  
}

// --- Function Definitions ---
uint8_t read_multiplexer(const int select_pins[3], int read_pin) {

  uint8_t readings = 0;

  // Iter through all pins combos
  for (uint8_t combo = 0; combo < 8; ++combo) {
    

    digitalWrite(select_pins[0], (combo >> 0) & 1);
    digitalWrite(select_pins[1], (combo >> 1) & 1);
    digitalWrite(select_pins[2], (combo >> 2) & 1);

    readings |= (digitalRead(read_pin) << combo);
  }

  // Reset all select pins
  for (int i = 0; i < 3; i++) {
    digitalWrite(select_pins[i], LOW);
  }

  return readings;
}


