/*
 * MicroCut.ino : power supply interruptions generator
 * author : JPP
 * V1.00 dated 06/11/2016
 */

int buttonPin = 13; // "Cut" button
int relayPin = A0;
int potPin = A1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // wait for "Cut" button release
  while(digitalRead(buttonPin) == LOW);
  
  // wait for "Cut" button press
  while(digitalRead(buttonPin) == HIGH);
  
  // read pot position
  int potPos = analogRead(potPin);
  
  // scale [0..1023] to [20000..50000] (20 to 50ms)
  long int microSeconds = 29.3255 * potPos + 20000.5;
  
  // pulse the relay for the required duration
  digitalWrite(relayPin, HIGH);
  delayMicroseconds(microSeconds - 5000); // remove 5ms for relay delay
  digitalWrite(relayPin, LOW);
  
  // send trace message to serial port
  Serial.print(0.001 * microSeconds);
  Serial.println(" ms");
  
  delay(200); // debouncing
}
