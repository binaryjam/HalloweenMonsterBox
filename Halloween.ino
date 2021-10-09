
  
#define ledPin 13
#define  LPWM_Output  6 // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

//PIR Pin 
#define pirPin 7 // Echo Pin
const int NORMALWAIT = 5000;
const int ANNOYWAIT = 420000;
const int MAXTRIGGERS = 7;

long postActiveWait = NORMALWAIT;
int annoyFactor = 0;
boolean motorOn = false;

long delayTime=3000;
int spinSpeed=90; 
  
void setup()
{
  //Enable the forward motion (not reverse) IBT-2 Pin
  pinMode(LPWM_Output, OUTPUT);

  pinMode(ledPin, OUTPUT);  
  pinMode(pirPin, INPUT);
   digitalWrite(13, LOW);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
}


void loop()
{
  
  boolean detected=false;
  
  detected = digitalRead(pirPin);
  Serial.print("Detected:");

  Serial.println(detected );
 
  if(detected)
  {
     motorOn=true;
  }

  
  if(motorOn)
  {
   Serial.print("motorOn:");

    digitalWrite(13, HIGH);
 
    // forward rotation
    analogWrite(LPWM_Output, 700);
    delay(delayTime);
    digitalWrite(LPWM_Output, LOW);

    motorOn=false;
    digitalWrite(13, LOW);
    Serial.print("motorOff:");
    
    delay(postActiveWait);
  
     annoyFactor++;
  
  }
  
  if (annoyFactor > MAXTRIGGERS)
  {
    annoyFactor=0;
    postActiveWait=ANNOYWAIT;
  }
  else
  {
       postActiveWait=NORMALWAIT;
  }

}



