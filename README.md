# Gesture-Controlled Robotic Car

Bachelor thesis project focused on the design and implementation of a gesture-controlled robotic car using ESP32 microcontrollers, an MPU6050 IMU, and Bluetooth Classic communication.

## Overview
The system consists of a wearable hand controller and a robotic car.  
Hand gestures are detected using an MPU6050 inertial measurement unit and translated into driving commands, which are transmitted wirelessly via Bluetooth to control the robot in real time.

## System Architecture
- **Transmitter (Hand Controller)**  
  ESP32 + MPU6050 IMU  
  Detects hand motion, applies calibration and filtering, and sends control commands.

- **Receiver (Robotic Car)**  
  ESP32 + L298N motor driver  
  Receives Bluetooth commands and drives the DC motors accordingly.

## Command Mapping
| Command | Action |
|--------|--------|
| F | Move forward |
| B | Move backward |
| L | Turn left |
| R | Turn right |
| S | Stop |

gesture-controlled-robotic-car/
├── transmitter/   # Hand controller firmware
├── receiver/      # Robotic car firmware
├── media/         # Images and demo media
├── .gitignore
└── README.md


## Hardware Components
- ESP32 DevKit (2×)
- MPU6050 IMU
- L298N motor driver
- DC motors
- Battery power supply

## How to Run
1. Upload the **receiver** firmware to the robot ESP32 and power it on
2. Upload the **transmitter** firmware to the hand controller ESP32
3. Keep the hand controller steady during the calibration phase
4. Move the hand to control the robot direction

## Media

![System Block Diagram](media/system_block_diagram.png)


## Notes
- Gesture thresholds and filter parameters were tuned experimentally
- Bluetooth Classic was selected to achieve low-latency real-time control

## Status
Bachelor thesis project – implementation completed.  
