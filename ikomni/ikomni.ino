#include "USBHost_t36.h"

// ===================== USB / Controller Setup =====================
USBHost myusb;
USBHub hub1(myusb); // Optional, but good practice
JoystickController joystick1(myusb);
BluetoothController bluet(myusb, true, "0000"); // For BT pairing

// ===================== Motor Setup =====================
const int M1_PWM = 3;  // Motor 1 PWM
const int M1_DIR = 22; // Motor 1 DIR
const int M2_PWM = 4;  // Motor 2 PWM
const int M2_DIR = 23; // Motor 2 DIRee
const int M3_PWM = 5;  // Motor 3 PWM
const int M3_DIR = 24; // Motor 3 DIR

// Distance from robot center to wheel (in meters, for rotation)
const float L = 0.1;

// ===================== Helper Functions =====================
// Maps the raw joystick integer value to a float from -1.0 to 1.0
float joyMap(int val) {
  return (float)val / 32767.0;
}

// Drives a motor with a given speed (-255 to 255)
void driveMotor(int pwmPin, int dirPin, float speed) {
  // Ensure speed is within the valid PWM range
  speed = constrain(speed, -255, 255);
  // Set direction based on the sign of the speed
  digitalWrite(dirPin, speed >= 0 ? HIGH : LOW);
  // Write the speed (magnitude) to the PWM pin
  analogWrite(pwmPin, abs(speed));
}

// ===================== Setup =====================
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial monitor to connect
  }
  Serial.println("Omni-Drive Robot Ready. Waiting for PS4 controller...");

  myusb.begin();

  // Set motor pins to OUTPUT
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
}

// ===================== Loop =====================
void loop() {
  myusb.Task(); // This must be called frequently to process USB events

  if (joystick1.available()) {
    // --- 1. Get Normalized Joystick Input with Deadzone ---
    const float DEADZONE = 0.10; // 10% deadzone to prevent drift

    // Correctly map joystick axes to robot movement
    float Vx_input = joyMap(joystick1.getAxis(0));   // Left Stick X -> Strafe
    float Vy_input = -joyMap(joystick1.getAxis(1));  // Left Stick Y -> Forward/Back (Inverted)
    float W_input  = joyMap(joystick1.getAxis(2));   // Right Stick X -> Rotation

    // Apply deadzone
    float Vx = (abs(Vx_input) > DEADZONE) ? Vx_input : 0;
    float Vy = (abs(Vy_input) > DEADZONE) ? Vy_input : 0;
    float W  = (abs(W_input)  > DEADZONE) ? W_input  : 0;

    // --- 2. Inverse Kinematics ---
    // Calculate the required speed for each wheel based on desired robot movement
    // The inputs (Vx, Vy, W) are still in the range -1.0 to 1.0
    float w1 = Vy + (L * W);
    float w2 = -0.866 * Vx - 0.5 * Vy + (L * W);
    float w3 =  0.866 * Vx - 0.5 * Vy + (L * W);

    // --- 3. Normalize Wheel Speeds ---
    // Find the maximum calculated speed (in magnitude)
    float max_speed = max(max(abs(w1), abs(w2)), abs(w3));

    // If the max speed is greater than 1.0, we must scale all speeds down
    // proportionally to prevent motor saturation and maintain the correct direction.
    if (max_speed > 1.0) {
      w1 /= max_speed;
      w2 /= max_speed;
      w3 /= max_speed;
    }

    // --- 4. Scale to PWM and Drive Motors ---
    // Convert the normalized speeds (-1.0 to 1.0) to the PWM range (-255 to 255)
    driveMotor(M1_PWM, M1_DIR, w1 * 255.0);
    driveMotor(M2_PWM, M2_DIR, w2 * 255.0);
    driveMotor(M3_PWM, M3_DIR, w3 * 255.0);

    // --- 5. Debugging Output (Optional) ---
    Serial.print("Vx: "); Serial.print(Vx, 2);
    Serial.print("\tVy: "); Serial.print(Vy, 2);
    Serial.print("\tW: "); Serial.print(W, 2);
    Serial.print("\t| w1: "); Serial.print(w1 * 255.0, 0);
    Serial.print("\tw2: "); Serial.print(w2 * 255.0, 0);
    Serial.print("\tw3: "); Serial.println(w3 * 255.0, 0);

    // Clear the joystick data to process the next packet
    joystick1.joystickDataClear();

  } else {
    // If controller disconnects, stop all motors for safety
    driveMotor(M1_PWM, M1_DIR, 0);
    driveMotor(M2_PWM, M2_DIR, 0);
    driveMotor(M3_PWM, M3_DIR, 0);
  }
}