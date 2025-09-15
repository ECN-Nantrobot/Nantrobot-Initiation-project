## Writing the code

### Introduction to Arduino Coding
Arduino is a simple platform for writing code and controlling hardware. To get started, you'll need:

- The Arduino IDE.
- The Arduino Uno connected to your computer via USB.

  
Steps:
- Install the Arduino IDE and open it on your computer.
- Select your Arduino board: Go to Tools > Board > Arduino Uno.
- Select the correct port: Go to Tools > Port and select the port your Arduino is connected to.
- Upload code: Write or paste your code into the IDE and click the Upload button (arrow icon) to transfer the code to your Arduino.

**Structure of the arduino code**
Arduino programs, or sketches, follow a simple structure that consists of two main functions:
1) Defining Pins and Variables (before setup)

  Before we dive into the core functions, we need to define the pins connected to various components (motors, sensors, etc.) and declare any variables we'll use later in the program.
  For example, we define the pins for the motors and sensors here:
  ```c++
#define motor1pin1 2  // Motor 1 control pin 1
#define motor1pin2 3  // Motor 1 control pin 2
#define R_S A1        // Right sensor pin
#define L_S A0        // Left sensor pin
```
2) ```setup()``` Function – **Runs Once**

  The ```setup()``` function is called once when the Arduino starts (or resets). This is where you define how each pin is used (either as an input or output), and initialize any other systems, like the serial communication to your computer.

  Example of what happens in setup():

- Pin Modes: Specify whether each pin is an input (to read data, e.g., from a sensor) or an output (to control something, like a motor).
- Serial Communication: Start the serial monitor with Serial.begin(9600) to print values for debugging.

```c++
void setup() {
  pinMode(motor1pin1, OUTPUT);  // Set motor control pins as output
  pinMode(motor1pin2, OUTPUT);
  pinMode(R_S, INPUT);          // Set sensor pins as input
  pinMode(L_S, INPUT);
  
  Serial.begin(9600);           // Start serial communication for debugging
}
```
3) ```loop()``` Function – Runs **Continuously**

The ```loop()``` function runs repeatedly after the setup. This is where you place your program's main logic, such as reading sensor values, controlling motors, or deciding how the robot should behave. This function runs continuously, meaning it keeps executing whatever logic you write until the Arduino is powered off or reset.

Inside the ```loop()```, you can:

- Read sensors using ```analogRead()``` to get data.
- Make decisions using ```if-else``` statements.
- Control motors using ```analogWrite()``` or ```digitalWrite()```.

```c++
void loop() {
  int R_S_value = analogRead(R_S);  // Read right sensor value
  int L_S_value = analogRead(L_S);  // Read left sensor value

  if (R_S_value > 150) {
    // Logic to control motors based on sensor values
  }
}
```

The Arduino runs the ```setup()``` function once, and then runs the ```loop()``` function over and over, controlling your robot based on the logic you program.

### Programming the Motors

We use an L298N motor driver to control two DC motors, allowing the robot to move forward, turn left, or turn right.

**Defining Motor Pins**

In the code, we define the pins connected to the motor driver:

```c++
#define motor1pin1 2  // Motor1 L298N Pin IN1
#define motor1pin2 3  // Motor1 L298N Pin IN2
#define motor2pin1 4  // Motor2 L298N Pin IN3
#define motor2pin2 5  // Motor2 L298N Pin IN4

#define motor1speed 9  // Motor1 speed control (L298N Pin ENA)
#define motor2speed 10 // Motor2 speed control (L298N Pin ENB)

void setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor1speed, OUTPUT);
  pinMode(motor2speed, OUTPUT);
}
```

- **Pin IN1/IN2** control the direction of Motor 1.
- **Pin IN3/IN4** control the direction of Motor 2.
- **ENA and ENB** control the speed of each motor via PWM (Pulse Width Modulation).

**Motor control logic**

We use the ```analogWrite()``` function to control motor speed and ```digitalWrite()``` to control direction. For example:

```c++
analogWrite(motor1speed, max_speed); // Set motor 1 to max speed
analogWrite(motor2speed, max_speed); // Set motor 2 to max speed

digitalWrite(motor1pin1, LOW); // Set motor 1 to move forward
digitalWrite(motor1pin2, HIGH); 

digitalWrite(motor2pin1, HIGH); // Set motor 2 to move forward
digitalWrite(motor2pin2, LOW);
```
(to put in the ```loop()``` fonction)

### Programming and Setting Detection Values for the Sensors

The robot uses two IR sensors to detect the line by measuring the amount of light reflected from the floor.

Left sensor (A0) and Right sensor (A1) read analog values, which vary depending on whether the sensor is over the black line or the lighter floor

```c++
#define R_S A1  // Right sensor
#define L_S A0  // Left sensor

void  setup(){
  pinMode(R_S, INPUT); // Set right sensor as input
  pinMode(L_S, INPUT); // Set left sensor as input

  Serial.begin(9600); // Start Serial Monitor for testing
}
```
**Reading Sensor Values**

The sensor values are read using ```analogRead()```, which gives a value between 0 and 1023.

```c++
int R_S_value = analogRead(R_S);
int L_S_value = analogRead(L_S);
```

**Display of the values**

To know what which value correspond to the black line we can display the values and move the robot on and off the line.
To do that we use ```Serial.print()``` to print values in the serial monitor (that you can open with the button on the top left corner).

```c++
Serial.print(R_S_value);  // Print right sensor value
Serial.print(",");
Serial.println(L_S_value); // Print left sensor value
```

### Combining the motors and sensors

We define a variable for the detection value

```c++
int detection_value = 150;
```

- If neither sensor detects the line, the robot is off the line, and both motor should run forward:

```c++
if (R_S_value < detection_value && L_S_value < detection_value) {
  // Both sensors are off the line, go straight forward
  digitalWrite(motor1pin1, LOW);  // Right motor forward
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH); // Left motor forward
  digitalWrite(motor2pin2, LOW);

  analogWrite(motor1speed, 150);   // Set the speed for the motors (if you go too fast the robot might miss the line)
  analogWrite(motor2speed, 150); 


}
```

- If only the right sensor detects the line, it means the robot needs to turn left. We slow the left motor down by making it stop and run the right motor forward:

```c++
else if (R_S_value > detection_value && L_S_value < detection_value) {
  // Right sensor detects the line, turn left
  digitalWrite(motor1pin1, LOW);  // Right motor forward
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);  // Stop left motor
  digitalWrite(motor2pin2, LOW);

  analogWrite(motor1speed, 150);   // Set the speed for the motors
  analogWrite(motor2speed, 0);     // maybe not stoping completly the motor but making it run slower is faster (you have to test it)
}
```

- If only the left sensor detects the line, the robot needs to turn right. The right motor stops while the left motor runs forward:

```c++
else if (L_S_value > detection_value && R_S_value < detection_value) {
  // Left sensor detects the line, turn right
  digitalWrite(motor1pin1, LOW);  // Stop right motor
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH); // Left motor forward
  digitalWrite(motor2pin2, LOW);

  analogWrite(motor1speed, 0);   // Set the speed for the motors
  analogWrite(motor2speed, 150);    
}
```

- If both sensors detect the line, the robot is over the line and should stop both motors:

```c++
else if (L_S_value > detection_value && R_S_value > detection_value) {
  // Both sensors detect the line, stop both motors
  digitalWrite(motor1pin1, LOW);  // Stop right motor
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);  // Stop left motor
  digitalWrite(motor2pin2, LOW);

  analogWrite(motor1speed, 0);   // Set the speed for the motors
  analogWrite(motor2speed, 0);    
}


