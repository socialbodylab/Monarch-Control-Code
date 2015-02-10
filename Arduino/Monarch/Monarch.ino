

                     /*\
                    /   \
                   /     \
                  /       \
                  -       - 
                     SBL
                     ^^^
                   MONARCH
                  -       -
                  \       /
                   \     /
                    \   /
                     \*/


#include <Servo.h>
#include <pt.h>    // Note: To run you need the protothread library! 

const float versionNumber = 3.5; //inc by <= 0.1 if not a new iteration.

/* ============================ */
/* Hello! specify which monarch you are going to upload this to */
const int prototypeNumber = 1; // currently: 1 or 4. They are Marked.
/* Thank You. */
/* ============================ */


// Program Definitions
/*   -----------
      \       /
       \     /
        \   /
         \*/

const int min_pw = 700;  // the shortest pulse sent to a servo
const int max_pw = 2300; // the longest pulse sent to a servo

const int numReadings = 20; // Sensitivity
int readings[numReadings]; // the readings from the analog input

//Some EMG data
int low   = 90;
int high  = 400;       
int index = 0;
int total = 0;   
int distributedValue = 0;

bool toggle = false;

int  demoThreshold = 0;
int  currentStage = 0;
int  currentStep = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


// THREADING
static struct pt  pt1, pt2, pt3, pt4, pt5;


// Data structure for sensor data
typedef struct
{
  int emg;
  int calibration;
  int mode;
  int emgPIN;
  int calPIN;
  int modPIN;
}  io_reader;

io_reader current;  // Store values here.
io_reader previous; // Same structure, but for storing previous values!


// Data structure to store servo positions
typedef struct
{
  Servo motor;
  int low;
  int high;
  int pos;
  int prevPos;
  int pin;
}  servos;

// There are two servos on each Monarch
servos rServo;
servos lServo;


         /*\
        /   \
       /     \
      /       \
      ---------  
  End of Definitions
-------------------------------------*/

void setup() {

  Serial.begin(9600); 

  PT_INIT( &pt1 );
  PT_INIT( &pt2 );
  PT_INIT( &pt3 );
  PT_INIT( &pt4 );
  PT_INIT( &pt5 );

  initData();

  pinMode(current.modPIN, INPUT_PULLUP);

  inputString.reserve(200);

} 

void loop() {

  serialIn();

  ioThread( &pt1, 4); // Input Thread

  switch (current.mode) {
    case 0:
      demo( &pt2, 50); // This mode is under demo.ino
      break;
    case 1:
      gradMode( &pt3, 4);
      break;
  }
  
  driver(   &pt4, 10);  // Writes to motor
  debugger( &pt5, 100); // Console Debugging

}

// Timing threads for I/O and Debugging
/*   -----------
      \       /
       \     /
        \   /
         \*/

// INPUT OUTPUT THREAD 
// - Handles data from the EMG, Adjusting Pot, and Toggle Button.
// ________________
/*| Don't Adjust-> |*/  static int ioThread( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| edit below  -v |*/
      
    int tempValue    = 0;
    int tempCalib    = 0;
    int mappedValue  = 0;
    int averageValue = 0;

    total = total - readings[index];        
    tempValue = analogRead(current.emgPIN);

    if(tempValue < low)
      low  = tempValue;
    if(tempValue > high)
      high = tempValue;

    mappedValue = map(tempValue, low, high, 0, 200);

    readings[index] = mappedValue;
    total  = total + readings[index];      
    index  = index + 1;                    

    if (index >= numReadings) {              
      index = 0;
      previous.emg = current.emg;       
    }

    averageValue = total / numReadings;
    current.emg = abs(averageValue);

    distributedValue = distributeEMG(current.emg);

    current.mode = digitalRead(current.modPIN);

    tempCalib = analogRead(current.calPIN);
    current.calibration = map(tempCalib, 0, 1023, 0, 200);


/*| edit above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//



// DEBUGGER - Controls Serial Output Timings
// ________________
/*| Don't Adjust-> |*/  static int debugger( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| Edit Below  -v |*/

    Serial.print(" | m: ");
    Serial.print(current.mode);   
    Serial.print(" | r: ");      
    Serial.print(rServo.pos);
    Serial.print(" | l:  "); 
    Serial.print(lServo.pos);
    Serial.print(" | cal: "); 
    Serial.print(current.calibration);
    Serial.print(" | emg: ");
    Serial.print(current.emg);
    Serial.print(" | Version: ");
    Serial.print(versionNumber);        
    Serial.println(" | ");   

    if (stringComplete) {
      Serial.println(inputString); 
      int temp = inputString.toInt();

      rServo.pos = temp;

      // clear the string:
      inputString = "";
      stringComplete = false;
    }

/*| Edit Above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//



         /*\
        /   \
       /     \
      /       \
      ---------  
End of the funky Threading Functions! 
-------------------------------------*/
