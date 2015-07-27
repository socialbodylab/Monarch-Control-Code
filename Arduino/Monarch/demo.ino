// Display Demo Mode,
// Allows for a long running EMG free application, with organic actuation.
/*   -----------
      \       /
       \     /
        \   /
         \*/

// TO-DO, Adjust to non reversed servos.

const int n = 3;
const int steps = 6;

typedef struct
{
  int interval;
  int duration;
  int pattern[steps];
} stages;

stages stage[n];

// State

int set_stages() {
  stage[0].interval = 160;
  stage[0].duration = 48;
  stage[0].pattern[0] = 0;
  stage[0].pattern[1] = 75;
  stage[0].pattern[2] = 75;
  stage[0].pattern[3] = 75;
  stage[0].pattern[4] = 75;
  stage[0].pattern[5] = 0;

  stage[1].interval = 200;
  stage[1].duration = 48;
  stage[1].pattern[0] = 0;
  stage[1].pattern[1] = 40;
  stage[1].pattern[2] = 60;
  stage[1].pattern[3] = 75;
  stage[1].pattern[4] = 40;
  stage[1].pattern[5] = 0;

  stage[2].interval = 100;
  stage[2].duration = 60;
  stage[2].pattern[0] = 0;
  stage[2].pattern[1] = 75;
  stage[2].pattern[2] = 60;
  stage[2].pattern[3] = 55;
  stage[2].pattern[4] = 75;
  stage[2].pattern[5] = 0;

  return true;
}

bool why = set_stages();

//// Require due to reversed servo positions.
//int p_pos (int l, int h, int pk) {
//  int r;
//
//  if (l > h) {
//    r = (((l - h) * ((100 - pk) / 100.0)) + h);
//  } else {
//    r = (((h - l) * (pk / 100.0)) + l);
//  }  
//
//  return (int) r;
//}

// DEMO   - Timed, non EMG, actuation of the servos.
// ________________
/*| Don't Adjust-> |*/  static int demo( struct pt *pt, long timeout ) { static long t = 0; PT_BEGIN( pt ); while(1) { PT_WAIT_UNTIL( pt, (millis() - t) > timeout );
/*| Edit Below  -v |*/

    demoThreshold++;

    if (demoThreshold == stage[currentStage].interval) {

    int c = stage[currentStage].pattern[currentStep];

    rServo.pos = c;
    lServo.pos = c;

    currentStep++;  

    } 

    if (currentStep > 0 && (demoThreshold >= (stage[currentStage].interval + ((stage[currentStage].duration / steps) * currentStep)))) {
      
      int temp, c;

      c = stage[currentStage].pattern[currentStep];

      temp = c;
      rServo.pos = temp; 

      temp = c;
      lServo.pos = temp;

      currentStep++;

    }

    if (currentStep >= steps) {
      currentStep = 0;
    } 

    if (demoThreshold >= (stage[currentStage].interval + stage[currentStage].duration)) {
      
      currentStage++;

      rServo.pos = rServo.low;
      lServo.pos = lServo.low;

      demoThreshold = 0; 

    }

    if (currentStage >= n) {
      currentStage = 0;
    }

/*| Edit Above -^  |*/
/*| Don't Adjust-> |*/  t = millis(); } PT_END( pt ); }
//|----------------|//

         /*\
        /   \
       /     \
      /       \
      ---------  

-------------------------------------*/
