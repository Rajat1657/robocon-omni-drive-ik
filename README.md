# 3-Wheel Omni Drive (Manual Control with PS4 controller + Teensy)

## Overview
This project is part of my SRM Team Robocon assignment.
Goal: Build a 3-wheel omni drive robot controlled by a PS4 controller via ESP32 + Teensy.

## Hardware
- Teensy 4.1
- ESP32 (Bluetooth bridge)
- 3 Omni wheels + motors
- Motor drivers (Cytron / BTS7960)
- PS4 Controller
- LiPo Battery (12–24V)

## Software
- Arduino IDE
- PS4-esp32 library
- Teensyduino

## 📐 Inverse Kinematics (IK)

For a **3-wheel omni drive** (wheels at 120° apart), joystick inputs  
(**Vx = forward/back**, **Vy = strafe**, **ω = rotation**) are converted into individual wheel speeds:

- $V_1 = V_x + \omega R$  
- $V_2 = -0.5V_x + 0.866V_y + \omega R$  
- $V_3 = -0.5V_x - 0.866V_y + \omega R$  

Where:  
- $V_1, V_2, V_3$ → wheel speeds  
- $R$ → distance from center to wheel  

**Examples:**  
- Forward → $V_1=+V_x$, $V_2=-0.5V_x$, $V_3=-0.5V_x$  
- Strafe right → $V_1=0$, $V_2=+0.866V_y$, $V_3=-0.866V_y$  
- Rotate CW → all wheels get $+\omega R$




## Daily Progress

### Day 1 (Sept 30)
- Watched videos on Inverse Kinematics
- Readied Basic Omni Drive Code
- Read ABU Robocon 2026 Problem Statement

### Day 2 (Oct 1)
- Set up the GitHub Repository
- Installed Arduino + Teensy + ESP32 support.
- Tested PS4-esp32 example.

### Day 3 (Oct 2)
- [log what you did...]

### Day 4 (Oct 3)


### Day 5 (Oct 4)


### Day 6 (Oct 5)
...

### Day 7 (Oct 6)
- Final testing, documentation complete.

## Results
- Robot moves in omni directions (forward, strafe, rotate).
- Robot can be controlled wirelessly using a PS4 controller.

## Future Improvements
- 
