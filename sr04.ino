
void initializeGPIO_SR04();
void sendTrigger(int triggerPin, int triggerTime_ms);
unsigned long measurePulse(int readPin);
int conversion(unsigned long duration_ms);

void setup() {
  initializeGPIO_SR04();
  Serial.begin(9600);
}

void loop() {
  sendTrigger(32, 50);
  Serial.println(conversion(measurePulse(30)));
}

// Assign GPIO
void initializeGPIO_SR04()
{
  pinMode(30, INPUT);
  pinMode(32, OUTPUT);
}


// Toggle the assigned pin HIGH for the assigned time in milliseconds.
void sendTrigger(int triggerPin, int triggerTime_ms)
{
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(triggerTime_ms);
  digitalWrite(triggerPin, LOW);
}

// This function measures an incoming pulse on the readPin - it waits for the pin to go high
// and returns the elapsed microseconds of the high duration
// TODO: Manage overflow of micros() function
unsigned long measurePulse(int readPin)
{
  unsigned long startTime_us, duration_us;
  
  while(!digitalRead(readPin))
  {
    ;
  }

  startTime_us = micros();

  while(digitalRead(readPin))
  {
    ;
  }

  duration_us = micros() - startTime_us;

  return duration_us;
}

// This function converts a microsecond duration to a distance as specified in the SR04 datasheet
int conversion(unsigned long duration_us)
{
  int range;
  
  range = duration_us / 58;

  return range;
}
