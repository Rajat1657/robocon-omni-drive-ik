# 3-Wheel Omni Drive (Manual Control with PS4 Controller + Teensy)

## 📌 Overview
This project is part of my **SRM's Robocon Club's assignment (Deadline: Oct 6, 2025)**.  
The goal is to build a **3-wheel omni drive robot** controlled wirelessly using a **controller**.  
The setup uses a **Teensy 4.1** as the main controller, with **ESP32** as a Bluetooth bridge for PS4 connectivity.  

---

## ⚙️ Hardware
- **Teensy 4.1** (Main controller, running IK + motor control)  
- **ESP32** (Handles Bluetooth communication with PS4 controller)  
- **3 Omni wheels** (120° configuration) + DC motors  
- **Motor Drivers** (Cytron / BTS7960)  
- **PS4 Controller**  
- **LiPo Battery** (12–24V)  

---

## 💻 Software
- Arduino IDE  
- Teensyduino  
- PS4-ESP32 library  

---

## 📐 Inverse Kinematics (IK)
For a **3-wheel omni drive** with wheels at **120° apart**, the velocity of each wheel is derived from the robot’s desired **linear velocity (Vx, Vy)** and **angular velocity (ω)**.  

Equations:

\[
V_1 = Vx \cdot \cos(0°) + Vy \cdot \sin(0°) + \omega \cdot R
\]

\[
V_2 = Vx \cdot \cos(120°) + Vy \cdot \sin(120°) + \omega \cdot R
\]

\[
V_3 = Vx \cdot \cos(240°) + Vy \cdot \sin(240°) + \omega \cdot R
\]

Where:  
- \(V_1, V_2, V_3\) = wheel speeds  
- \(Vx\) = forward/backward velocity  
- \(Vy\) = left/right (strafing) velocity  
- \(\omega\) = rotational velocity (yaw)  
- \(R\) = distance from robot center to wheel  

---

## 📅 Daily Progress

### Day 1 (Sept 30)
- Watched videos on Inverse Kinematics.  
- Readied basic omni drive equations.  
- Studied ABU Robocon 2026 problem statement.  

### Day 2 (Oct 1)
- Set up GitHub repository for the project.  
- Installed Arduino IDE + Teensyduino + ESP32 board support.  
- Ran and tested **PS4-ESP32 example** (Bluetooth pairing successful).  

### Day 3 (Oct 2)
- Write and test **IK calculation functions** in Arduino code.  
- Map PS4 controller joysticks → Vx, Vy, ω values.  
- Simulate motor outputs on Serial Monitor.  

### Day 4 (Oct 3)
- Connect Teensy with **motor driver + one motor**.  
- Verify forward/backward control.  
- Debug motor direction and PWM scaling.  

### Day 5 (Oct 4)
- Connect all 3 motors.  
- Test omni movement (forward, strafe, diagonal).  
- Adjust scaling and verify IK correctness.  

### Day 6 (Oct 5)
- Integrate **rotation control** using PS4 joystick.  
- Fine-tune speed and responsiveness.  
- Record testing video.  

### Day 7 (Oct 6)
- Final testing of full system (wireless control).  
- Complete documentation (README + comments in code).  
- Submit assignment. ✅  

---

## ✅ Results
- Robot moves smoothly in omni directions (forward, strafe, rotate).  
- Wireless control via PS4 controller works successfully.  
- IK equations verified in real movement.  

---

## 🚀 Future Improvements
- Add **PID control** for precise motion.  
- Implement **deadzone filtering** for joysticks.  
- Add **sensor feedback** (IMU, encoders) for stability.  
- Optimize ESP32–Teensy communication latency.  

---

## 📚 References
- [Omni Wheel IK basics (YouTube)](https://www.youtube.com/shorts/0_uKG0Q1ztI)  
- PS4-ESP32 Arduino library (GitHub)  
- Teensyduino documentation  
