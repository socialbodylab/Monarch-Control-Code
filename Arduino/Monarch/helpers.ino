/* Helper functions */

int multiMap(int val, int* _in, int* _out, uint8_t size) {
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];
  uint8_t pos = 1;
  while(val > _in[pos]) pos++;
  if (val == _in[pos]) return _out[pos];
  return map(val, _in[pos-1], _in[pos], _out[pos-1], _out[pos]);
}

int distributeEMG(int val) {

  int tempPos = 0;

  if (val >= current.calibration) {

    int out[] = { 0, 20, 300, 800, 1200, 1600, 2000, 2000, 2000, 2000, 2000};
    int in[]  = { 0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200}; 

    int x = multiMap(val, in, out, 11);

    // Servo positions are the same now. `lServo` here is valid.
    tempPos = map(x, 0, 2000, lServo.low, lServo.high);

  } else {
    tempPos = 0;
  }

  return tempPos;
}
