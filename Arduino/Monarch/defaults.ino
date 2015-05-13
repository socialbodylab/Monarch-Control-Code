
/* =============================================== */
/* ========= Prototype Specific Defaults ========= */

typedef struct
{
  int high;
  int low;
  int leftPIN;
  int rightPIN;
  int emgPIN;
  int calPIN;
  int modPIN;

}  prototype;

prototype monarch;

void prototypeDefaults() {

	monarch.high  		= 86;
	monarch.low   		= 4;
	monarch.leftPIN   	= 8;
	monarch.rightPIN 	= 9;
	monarch.emgPIN 		= A0;
	monarch.calPIN 		= A1;
	monarch.modPIN 		= 2;

}

/* =============================================== */
/* =========             Data            ========= */

int initData() {
  /* Load prototype Defaults */
  prototypeDefaults();

  /* Left Servo Setup */
  lServo.high          = monarch.high;
  lServo.low           = monarch.low;
  lServo.pos           = lServo.low; // Sets initial position to down
  lServo.pin           = monarch.leftPIN;  

  lServo.motor.attach(lServo.pin);
  lServo.motor.write( lServo.low);

  /* Right Servo Setup */
  rServo.high          = monarch.high;
  rServo.low           = monarch.low;
  rServo.pos           = rServo.low; // Sets initial position to down
  rServo.pin           = monarch.rightPIN;
  
  rServo.motor.attach(rServo.pin);
  rServo.motor.write( rServo.low);  

  /* Safe defaults for other IO */
  current.emg          = 0;
  current.calibration  = 0;
  current.mode         = 1;
  current.emgPIN 	   = monarch.emgPIN;
  current.calPIN 	   = monarch.calPIN;
  current.modPIN 	   = monarch.modPIN;

  previous.emg         = 0;
  previous.calibration = 0;
  previous.mode        = 0;
  previous.emgPIN 	   = 0;
  previous.calPIN 	   = 0;
  previous.modPIN 	   = 0;

  /* Setsup Smoothing Array*/
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  

}
