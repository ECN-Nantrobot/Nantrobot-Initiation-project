#define R_S A1  // Right sensor pin
#define L_S A0  // Left sensor pin

void setup() {
  pinMode(R_S, INPUT); // Set right sensor as input
  pinMode(L_S, INPUT); // Set left sensor as input

  Serial.begin(9600); // Start Serial Monitor for testing
}

void loop() {
  // Read sensor values
  int R_S_value = analogRead(R_S);  // Read right sensor value
  int L_S_value = analogRead(L_S);  // Read left sensor value

  // Print sensor values to Serial Monitor
  Serial.print("Right Sensor Value: ");
  Serial.print(R_S_value);
  Serial.print(", Left Sensor Value: ");
  Serial.println(L_S_value);

  // Optional: Add a delay for readability
  delay(500); // Adjust the delay as needed (500ms is used here)
}
