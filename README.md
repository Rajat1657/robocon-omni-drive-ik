# 3-Wheel Omni Drive (Manual Control with PS4 controller + Teensy)

## Overview
This project is part of my SRM Team Robocon assignment.
Goal: Build a 3-wheel omni drive robot controlled by a PS4 controller via Teensy and Bluetooth Module.

## Hardware
- Teensy 4.1
- Bluetooth Dongle
- 3 Omni wheels + motors
- Motor drivers
- PS4 Controller
- LiPo Battery (12–24V)

## Software
- Arduino IDE
- PS4 library
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

## Results
- Robot moves in omni directions (forward, strafe, rotate).
- Robot can be controlled wirelessly using a PS4 controller.

## Future Improvements
- 

## Reference
[3-Wheel-Omni-Drive-KI](https://www.youtube.com/watch?v=wwQQnSWqB7A)
[Inverse-Kinematics](https://www.youtube.com/watch?v=1-FJhmey7vk)
[]
