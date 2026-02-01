# Transmitter – ESP32 Hand Controller

This module is the wearable hand controller of the gesture-controlled robotic car.  
It uses an MPU6050 IMU to detect hand motion and sends driving commands to the robot via Bluetooth Classic.

## Function
- Reads acceleration data from the MPU6050 sensor
- Performs calibration at startup (neutral hand position)
- Applies smoothing and a dead zone to reduce noise
- Sends single-character commands to the robot in real time

## Bluetooth
- Device name (client): `ESP32_TRANSMITTER`
- Connects automatically to receiver: `ESP32_ROBOT`

## Command Mapping
| Command | Action |
|--------|--------|
| F | Move forward |
| B | Move backward |
| L | Turn left |
| R | Turn right |
| S | Stop |

## Hardware
- ESP32 DevKit
- MPU6050 IMU
- Battery supply

## Usage
1. Upload the **receiver code** to the robot ESP32 and power it on
2. Upload this transmitter code to the hand controller ESP32
3. Keep the hand steady during the calibration phase
4. Move the hand to control the robot direction

## Notes
- Gesture thresholds and filter parameters were tuned experimentally
- Communication is based on Bluetooth Classic for low latency
