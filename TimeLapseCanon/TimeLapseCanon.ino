// INPUT OUTPUT CONFIGURATION

const int button = 13;
const int ShutterPin = 2;
const int FocusPin = 3;

//Button Debounce
int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
int reading;

//Shutter Control
int ShutterControl = LOW;
long ShutterDelay = 2000;
long lastShutterRelease;
int ShutterCount = 10;
int ShutterCountCurrent = 0;

void setup()
{
  pinMode(button, INPUT);
  pinMode(ShutterPin, OUTPUT);
  pinMode(FocusPin, OUTPUT);
  long lastShutterRelease = millis();
}

void loop()
{
 
  reading = digitalRead(button);
  if (reading != lastButtonState) {
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
          buttonState = reading;
          if (buttonState == HIGH) {
            ShutterControl = !ShutterControl;
          }  
      }
  }
  
  if (ShutterControl == HIGH) {
    if ((lastShutterRelease + ShutterDelay) < millis()) {
      ShutterRelease();
      lastShutterRelease = millis();
      ShutterCountCurrent++;
    }
   if (ShutterCountCurrent >= ShutterCount) {
      ShutterControl = LOW;
      ShutterCountCurrent = 0;
    }
  }
    
  lastButtonState = reading;
}

void ShutterRelease(){
  digitalWrite(ShutterPin, HIGH);
  delay(300);
  digitalWrite(ShutterPin, LOW);
}
