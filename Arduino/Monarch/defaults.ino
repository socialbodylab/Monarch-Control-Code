
/* =============================================== */
/* ========= Prototype Specific Defaults ========= */

typedef struct
{
  int leftHIGH;
  int leftLOW;
  int leftPIN;
  int rightHIGH;
  int rightLOW;
  int rightPIN;
  int emgPIN;
  int calPIN;
  int modPIN;

}  prototype;

prototype M1;
prototype M2;
prototype M3;
prototype M4;
prototype monarch; // Is eventually set to one of the 'M(onarchs)' above.

void prototypeDefaults() {

	//Monarch I
	M1.leftHIGH  = 170;
	M1.leftLOW   = 90;
	M1.leftPIN   = 8;
	M1.rightHIGH = 10;
	M1.rightLOW  = 90;
	M1.rightPIN  = 9;
	M1.emgPIN = A0;
	M1.calPIN = A1;
	M1.modPIN = 2;

	//Monarch II
	M2.leftHIGH  = 170;
	M2.leftLOW   = 90;
	M2.leftPIN   = 8;
	M2.rightHIGH = 10;
	M2.rightLOW  = 90;
	M2.rightPIN  = 9;
	M2.emgPIN = A0;
	M2.calPIN = A1;
	M2.modPIN = 2;

	//Monarch III
	M3.leftHIGH  = 160;
	M3.leftLOW   = 90;
	M3.leftPIN   = 8;
	M3.rightHIGH = 20;
	M3.rightLOW  = 90;
	M3.rightPIN  = 9;
	M3.emgPIN = A0;
	M3.calPIN = A1;
	M3.modPIN = 2;

	//Monarch IV
	M4.leftHIGH  = 160;
	M4.leftLOW   = 90;
	M4.leftPIN   = 8;
	M4.rightHIGH = 10;
	M4.rightLOW  = 90;
	M4.rightPIN  = 9;
	M4.emgPIN = A0;
	M4.calPIN = A1;
	M4.modPIN = 2;

	// Sets the data of current to which you are working on.
	switch (prototypeNumber) {
	    case 1:
	      monarch = M1;
	      break;
	    case 2:
	      monarch = M2;
	      break;
	    case 3:
	      monarch = M3;
	      break;
	    case 4:
	      monarch = M4;
	      break;
  	}

}

/* =============================================== */
/* =========             Data            ========= */

int initData() {
  /* Load prototype Defaults */
  prototypeDefaults();

  /* Left Servo Setup */
  lServo.high          = monarch.leftHIGH;
  lServo.low           = monarch.leftLOW;
  lServo.pos           = lServo.low; // Sets initial position to down
  lServo.pin           = monarch.leftPIN;  

  lServo.motor.attach(lServo.pin,min_pw,max_pw);
  lServo.motor.write( lServo.low);

  /* Right Servo Setup */
  rServo.high          = monarch.rightHIGH;
  rServo.low           = monarch.rightLOW;
  rServo.pos           = rServo.low; // Sets initial position to down
  rServo.pin           = monarch.rightPIN;
  
  rServo.motor.attach(rServo.pin,min_pw,max_pw);
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

  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  

}
