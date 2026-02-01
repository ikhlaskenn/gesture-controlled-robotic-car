ESP32 robotic car receiver code (Bluetooth + motor control).
# Receiver – ESP32 Robotic Car

This folder contains the ESP32 firmware for the robotic car (receiver side).  
The receiver connects to the wearable transmitter via Bluetooth Classic and controls the DC motors based on received gesture commands.

## Function
- Receives single-character commands via Bluetooth (`F`, `B`, `L`, `R`, `S`)
- Decodes commands in real time
- Drives motors through an L298N motor driver

## Command Mapping
| Command | Action |
|-------|--------|
| F | Move forward |
| B | Move backward |
| L | Turn left |
| R | Turn right |
| S | Stop |

## Hardware
- ESP32 DevKit
- L298N motor driver
- DC motors
- External power supply

## Notes
- A safety timeout stops the motors automatically if communication is lost.
- Bluetooth device name: `ESP32_ROBOT`
