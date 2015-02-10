
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
  int out[] = { 0, 20, 300, 800, 1200, 1600, 2000, 2000, 2000, 2000, 2000};
  int in[]  = { 0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200}; 

  int x = multiMap(val, in, out, 11);

  return x;
}

void serialIn() {
    while (Serial.available()) {

    char inChar = (char)Serial.read(); 

    inputString += inChar;

      if (inChar == '\n') {
        stringComplete = true;
      } 
    }
}