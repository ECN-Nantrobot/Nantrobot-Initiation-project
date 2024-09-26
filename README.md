# Nantrobot-Initiation-project

Welcome to the Nantrobot Club ! This project serves as an initiation for first-year students at Centrale Nantes to learn the basics of Arduino programming by building a line-following robot.

This repository contains all the resources needed to build and program a functional robot, including:

**CAD files** for the robot
**Documentation** to guide students at different skill levels
**Example code** for individual components (sensors and motors) and the full robot
**Hardware overview** (Arduino, L298N motor driver, IR sensors, DC motors, and 9V battery)
The documentation is designed to be progressive:
-If you already have some Arduino experience, just read the first section, which provides an overview of the robot.
-For those less familiar with Arduino, follow the full documentation on how to wire the robot and write the code.

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="##Introduction">Introduction</a></li>
    <li><a href="##Wiring">Wiring</a></li>
  </ol>
</details>



## Introduction
The robot moves using two **DC motors** attached to wheels and one **castor wheel** for stability. These motors are powered by a **9V battery** and controlled by the Arduino through a **motor driver** (L298N). The motor driver acts as a bridge, allowing the Arduino to control the speed and direction of the motors while providing the necessary power from the battery.

To detect the line, the robot uses two **infrared (IR) sensors**. Each IR sensor has two parts:

- An IR LED that shines infrared light onto the ground.
- An IR receiver that measures how much of that light is reflected back.
The sensors can tell the difference between the black line and the lighter floor:

- **Black absorbs more light**, so less is reflected back.
- **The lighter floor reflects more light**, so the sensor detects a stronger signal.
By constantly reading the sensors, the robot can "see" the line and adjust its movement to stay on track.

Finally to make the robot follow the line we just need to adjust it's trajectory based on which sensor is detecting the line : 
- none of them = moving forward
- one of them = turning in the opposite direction (this can be done with many ways like only activating on motor or slowing just one motor etc...)
- both motor = stop you've succesfully arrived to the finish line !
![Logic](https://github.com/user-attachments/assets/50dcd3e0-1759-4c92-8070-2c8b08c522ae)


Before diving into the details, take a look at the 3D rendering of the robot below. This will give you a clear understanding of how everything fits together.

![assembly detail](https://github.com/user-attachments/assets/7a5bcbd7-bee0-4ddb-a628-69a2c5180cea)


For those who already have experience with Arduino and robotics, this overview should be enough to get you started. If you need more specific details on any component, feel free to look them up on google as that's how we usualy work on project.

## Wiring

### Step-by-Step Wiring Guide
**Power Connections**

- Connect the 9V battery to the L298N motor driver's power terminals to provide power to the motors.
- Connect the GND (ground) pin of the motor driver to the GND pin on the Arduino.


**Motor Connections**

- Attach the two DC motors to the OUT1 and OUT2 terminals on the motor driver (for one motor), and OUT3 and OUT4 for the second motor.
- This allows the motor driver to control the motors' speed and direction.


**Motor Driver to Arduino**

- Use jumper wires to connect the input pins (IN1, IN2, IN3, IN4) on the motor driver to the digital pins on the Arduino (e.g., D2, D3, D4, D5). These connections will allow the Arduino to control the motor driver and, in turn, the motors.
- Use jumper wires to conntect the enable pins A and B on the motor driver to the digital pins on the Arduino (e.g., D9, D10). These connections will allow to control the speed of the motors.


**IR Sensor Connections**

- Connect the VCC pin of each IR sensor to the **3.3V pin** on the Arduino, and the GND pin of each sensor to the Arduino’s GND.
- Attach the A0 pin of each sensor to an available analog pin on the Arduino (e.g., A0 for the left sensor and A1 for the right sensor). This will let the Arduino read the sensor values to detect the line.
(Note: On some sensors, you will also find a D0 pin, which outputs a digital signal that simply indicates whether or not the line is detected. The sensitivity can be adjusted using a built-in potentiometer. However, since not all sensors have this option, we will not be using the D0 pin for this project to keep things consistent and fair for everyone.)

**Final Check**

Make sure all your connections are secure and match the schematic. The motors should be powered through the motor driver, and both the sensors and Arduino should be connected to the correct pins.

### Full Schematic

![schematics](https://github.com/user-attachments/assets/00a609c8-6228-4e16-ad74-812fd70c3853)


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

- If neither sensor detects the line, the robot is off the line, and both motors should run forward:

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


