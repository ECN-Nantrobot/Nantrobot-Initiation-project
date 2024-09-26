// # 1 ----- definition of pins and variables

// Pins for the motor driver
 #define motor1pin1 2 //Motor1  L293 Pin in1
 #define motor1pin2 3 //Motor1  L293 Pin in1
 #define motor2pin1 4 //Motor2  L293Pin in1
 #define motor2pin2 5 //Motor2  L293 Pin in1

 #define motor1speed 9 //Enable1 L293 Pin enA
 #define motor2speed 10 //Enable2 L298 Pin enB

 // Pins for the sensors
 #define R_S A1 // Right sensor
 #define L_S A0 // Left sensor

// Variable definition
int turning_speed = 0;                                                             
int max_speed = 100;

int detection_value = 150;

bool line_left = false;
bool line_right = false;

// setup fonction (run only once) define if pins are input or output

void  setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor1speed, OUTPUT);
  pinMode(motor2speed, OUTPUT);

  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);

  Serial.begin(9600);
}

// 2 --- Loop fonction (run indefinitely)

int R_S_value = 0;
int L_S_value = 0;

void loop() {

  // Read value of both sensor
  R_S_value=analogRead(R_S);
  L_S_value=analogRead(L_S);

  Serial.print(R_S_value);
  Serial.print(",");
  Serial.print(L_S_value);
  Serial.print(",");


  // Decide if there is the line or not (to know the value print the value and test with/without the line)
  if(R_S_value > detection_value){
    line_right = true;
  }else{
    line_right = false;
  }

  if(L_S_value > detection_value) {
    line_left = true;
  }else {
    line_left = false;
  }
  
  Serial.print(line_right);
  Serial.print(",");
  Serial.println(line_left);

  // Activate the motors based on the sensor result
  if(!(line_left && line_right)) {
    // if both sensor are not activated we switch on both motors 
    // The we set the speed of each motor depending on what we need to do

    
    if(!line_left && !line_right) {
      // If both sensor don't detect the line both motor go full speed.
      analogWrite(motor1speed, max_speed);
      analogWrite(motor2speed, max_speed); 


    }else if(!line_left && line_right) {
      // If we only detect the right line we need to turn left
      // so the right motor go full speed and the left one a bit slower

      analogWrite(motor1speed, max_speed);
      analogWrite(motor2speed, turning_speed);

    }else if(line_left && !line_right) {
      // And the oposite if we only detect the left line

      analogWrite(motor1speed, turning_speed);
      analogWrite(motor2speed, max_speed);
    }

    //TODO: check if I can put it up
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

  }else {
    // Else if we detect the line on both sensors we stop both motors

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
  }
}
