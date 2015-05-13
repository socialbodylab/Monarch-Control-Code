// Timing threads for Modes and the 'Driver'
/*   -----------
      \       /
       \     /
        \   /
         \*/



int  iterations = 0;


// TOGGLE MODE - The initial mode we worked with
//             - Flex to raise and Flex to lower
// ________________
/*| Don't Adjust-> |*/  static int toggMode( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| edit below  -v |*/

    iterations++;

    if ((current.emg - previous.emg) >= (current.calibration / 4) 
        and (current.emg >= current.calibration) and (iterations >= 125)) 
    {
      toggle = !toggle;
      iterations = 0;
    }

  
    if (toggle) 
    {
      rServo.pos = rServo.low;
      lServo.pos = lServo.low;
    } else {
      rServo.pos = rServo.high;
      lServo.pos = lServo.high;
    }


/*| edit above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//




// HOLD MODE - A new mode
//           - Flex to raise, Relax to lower (non gradual)
// ________________
/*| Don't Adjust-> |*/  static int holdMode( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| edit below  -v |*/

    if (current.emg >= current.calibration) {
      rServo.pos = rServo.high;
      lServo.pos = lServo.high;
    } else {
      rServo.pos = rServo.low;
      lServo.pos = lServo.low;
    }

/*| edit above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//




// GRADUAL MODE - A new mode
//              - Gradually raises and lowers based directly on flex data
// ________________
/*| Don't Adjust-> |*/  static int gradMode( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| edit below  -v |*/

    int diff = abs(lServo.pos - distributedValue);

    if(diff > 4) {
      rServo.pos     = distributedValue;
      rServo.prevPos = distributedValue;
      lServo.pos     = distributedValue;
      lServo.prevPos = distributedValue;
    }

/*| edit above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//



  
// DRIVER   - Drives them servos!
// ________________
/*| Don't Adjust-> |*/  static int driver( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| Edit Below  -v |*/

    lServo.motor.write(lServo.pos);
    rServo.motor.write(rServo.pos);
    
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