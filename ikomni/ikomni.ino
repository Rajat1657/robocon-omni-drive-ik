#include <USBHost_t36.h>  // This library lets the Teensy talk to USB devices like a PS4 controller

// These are the pins connected to the Cytron
int pwm1 = 23;  // Motor 1 pwm
int dir1 = 21;  // Motor 1 direction control

int pwm2 = 3;   // Motor 2 pwm
int dir2 = 5;   // Motor 2 direction control

int pwm3 = 2;   // Motor 3 pwm
int dir3 = 4;   // Motor 3 direction control

// L is the distance from the center of the robot to each wheel
// r is the radius of the wheel
float L = 0.315;
float r = 0.1;

// These will hold the required movement direction and rotation
float Vx = 0.0;  // Forward/backward
float Vy = 0.0;  // Left/right
float w = 0.0;   // Rotation (spin)

int pwmVal = 0;         // Final PWM value sent to motors
float maxSpeed = 0.2;   // Maximum speed in meters per second

// === Joystick filtering ===
int deadZone = 20;  // deadzone to avoid unnnecessary movement or jitters

// === USB controller setup ===
USBHost myusb;                            // USB host object for Teensy
BluetoothController bluet(myusb, true, "0000");  // for pairing the PS4
JoystickController joystick(myusb);      // Joystick object to read PS4 inputs

// === Setup runs once at startup ===
void setup() {
  Serial.begin(115200);  // Start serial monitor for debugging
  while (!Serial && millis() < 4000);  // Wait up to 4 seconds for serial to connect
  Serial.println("Waiting for PS4 controller...");

  myusb.begin();  // Start USB host

  // Set all motor pins as outputs
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);

  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);

  pinMode(pwm3, OUTPUT);
  pinMode(dir3, OUTPUT);
}


void loop() {
  myusb.Task();  // Keep USB host running to check for controller input

  if (joystick.available()) {  // if controller is connected and sending data

    // read joystick axes and map them from 0–255 to -127 to +127
    int lx = map(joystick.getAxis(1), 0, 255, -127, 127);  // Left stick X axis (for strafing left and right)
    int ly = map(joystick.getAxis(2), 0, 255, -127, 127);  // Left stick Y axist (forward/backward)
    int rx = map(joystick.getAxis(3), 0, 255, -127, 127);  // Right stick X axis (rotation)

    // Apply deadzone to ignore small movements
    if (abs(lx) < deadZone) lx = 0;
    if (abs(ly) < deadZone) ly = 0;
    if (abs(rx) < deadZone) rx = 0;

    // Print joystick values for debugging
    Serial.print("LX: "); Serial.print(lx);
    Serial.print(" | LY: "); Serial.print(ly);
    Serial.print(" | RX: "); Serial.println(rx);

    // Convert joystick values to motion commands
    Vx = -((float)ly / 127.0);  // Forward/backward (invert Y)
    Vy = -((float)lx / 127.0);  // Left/right (invert X)
    w  =  ((float)rx / 127.0);  // Rotation

    // Calculate how fast each wheel should spin to achieve the desired motion
    float w1 = ((-0.866 * Vx - 0.5 * Vy + L * w) / r);  // Wheel 1
    float w2 = (( 0.866 * Vx - 0.5 * Vy + L * w) / r);  // Wheel 2
    float w3 = (( 0.0   * Vx + 1.0 * Vy + L * w) / r);  // Wheel 3

    // Send speed commands to each motor
    setMotor(pwm1, dir1, -w1);  // Motor 1 (inverted) (because the controller takes up as negative and down as positive)
    setMotor(pwm2, dir2,  w2);  // Motor 2
    setMotor(pwm3, dir3,  w3);  // Motor 3

    // Print calculated speeds for debugging
    Serial.print(" || Vx: "); Serial.print(Vx);
    Serial.print(" | Vy: "); Serial.print(Vy);
    Serial.print(" | w1: "); Serial.print(w1);
    Serial.print(" | w2: "); Serial.print(w2);
    Serial.print(" | w3: "); Serial.println(w3);

    joystick.joystickDataClear();  // Clear joystick data for next loop
  }
}

// This sets the direction and PWM for a motor based on desired speed
void setMotor(int pwm, int dir, float speed) {
  // Convert speed to PWM value (scaled to 0–100 range)
  int pwmVal = mapFloatToInt(abs(speed) * 1000, 0, maxSpeed * 10000, 0, 100);
  pwmVal = constrain(pwmVal, 0, 100);  // Clamp to safe range

  if (pwmVal < 5) pwmVal = 0;  // Ignore very low speeds to prevent jitter

  // Set motor direction and apply PWM
  if (speed > 0) {
    digitalWrite(dir, HIGH);         // Forward
    analogWrite(pwm, pwmVal);
  } else if (speed < 0) {
    digitalWrite(dir, LOW);          // Reverse
    analogWrite(pwm, abs(pwmVal));
  } else {
    analogWrite(pwm, 0);             // Stop
  }