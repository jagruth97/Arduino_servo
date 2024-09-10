#include "Servo.h"

Servo servo;

// Declare pin variables
int Signal = 8;     // Pin connected to the sensor (e.g., IR sensor or button)
int servopin = 9;   // Pin connected to the servo motor control
char data = 0;      // Variable to store data received via serial communication
int led = 13;       // Pin connected to an LED for visual feedback

// Setup function runs once when the microcontroller starts
void setup() {
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set pin modes
  pinMode(Signal, INPUT);    // Set Signal pin as input to read the sensor
  pinMode(led, OUTPUT);      // Set led pin as output to control the LED

  // Attach the servo to the servopin and close the cap (initial position)
  servo.attach(servopin);
  servo.write(0);  // Close the cap on power on
  delay(1000);     // Wait for a second
  servo.detach();  // Detach the servo to save power
}

// Loop function runs continuously after the setup
void loop() {
  // Read the state of the sensor (button or IR sensor)
  int buttonState = digitalRead(Signal);
  delay(1);  // Small delay to stabilize reading

  // Check if there is any data available in the serial buffer
  if (Serial.available() > 0) {
    data = Serial.read();    // Read the incoming serial data
    Serial.print(data);      // Print the received data to the serial monitor

    // Control the LED based on received serial data
    if (data == '1') {
      digitalWrite(led, HIGH);   // Turn on the LED if '1' is received
    } else if (data == '0') {
      digitalWrite(led, LOW);    // Turn off the LED if '0' is received
    }
  }

  // If the sensor is triggered (button pressed or IR sensor detects an object)
  if (buttonState == 0) {
    servo.attach(servopin);  // Attach the servo to control it
    delay(1);                // Small delay for servo attachment

    // Open the cap by rotating the servo to 90 degrees
    servo.write(90);
    delay(1000);             // Keep the cap open for 1 second

    // Close the cap by rotating the servo back to 0 degrees
    servo.write(0);
    delay(1000);             // Keep the cap closed for 1 second

    servo.detach();          // Detach the servo to save power
  }
}
