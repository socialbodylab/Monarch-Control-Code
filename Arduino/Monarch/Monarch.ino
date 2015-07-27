

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
// Edit info

#include <Servo.h>
#include <pt.h>    // Note: To run you need the protothread library! 
                   // It should be in this repository under ../libraries

const float versionNumber = 5.0; //inc by <= 0.1 if not a new iteration.

// Program Definitions
/*   -----------
      \       /
       \     /
        \   /
         \*/

const int numReadings = 20; // Sensitivity
int readings[numReadings];  // the readings from the analog input

//Some EMG data
int low   = 90;
int high  = 400;       
int index = 0;
int total = 0;   
int distributedValue = 0;

bool toggle = false;

/* Demo Globals */
int  demoThreshold = 0;
int  currentStage = 0;
int  currentStep = 0;

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

  PT_INIT( &pt1 );
  PT_INIT( &pt2 );
  PT_INIT( &pt3 );
  PT_INIT( &pt4 );
  PT_INIT( &pt5 );

  initData();

  pinMode(current.modPIN, INPUT_PULLUP);

} 

void loop() {

  //serialIn();

  ioThread(     &pt1, 4); // Input Thread

  switch (current.mode) {
    case 0:
      demo( &pt2, 40);
      break;
    case 1:
      gradMode( &pt3, 4);
      break;
  }
  
  driver(       &pt4, 20);  // Writes to motor
  debugger(     &pt5, 100); // Console Debugging

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
      
    int emgMoment    = 0;
    int tempCalib    = 0;
    int mappedMoment = 0;
    int averageValue = 0;

    current.mode = digitalRead(current.modPIN);

    tempCalib = analogRead(current.calPIN);
    current.calibration = map(tempCalib, 0, 1023, 0, 200);

    /* Smoothing: */

    total = total - readings[index];        
    emgMoment = analogRead(current.emgPIN);

    if(emgMoment < low)
      low  = emgMoment;
    if(emgMoment > high)
      high = emgMoment;

    mappedMoment = map(emgMoment, low, high, 0, 200);

    readings[index] = mappedMoment;
    total  = total + readings[index];      
    index  = index + 1;                    

    if (index >= numReadings) {              
      index = 0;
      previous.emg = current.emg;       
    }

    averageValue = total / numReadings;
    current.emg = abs(averageValue);

    distributedValue = distributeEMG(current.emg);


/*| edit above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//



// DEBUGGER - Controls Serial Output Timings
// ________________
/*| Don't Adjust-> |*/  static int debugger( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| Edit Below  -v |*/

    Serial.print(" | m: ");
    Serial.print(current.mode);   
    Serial.print(" | p: ");      
    Serial.print(rServo.pos);
    Serial.print(" | cal: "); 
    Serial.print(current.calibration);
    Serial.print(" | emg: ");
    Serial.print(current.emg);
    Serial.print(" | Version: ");
    Serial.print(versionNumber);        
    Serial.println(" | ");   

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
