/*
Creates array with number of engine steps required for each key
Written by Sebastian Kaczor
*/
#pragma once

#define F3 0
#define FIS3 1
#define G3 2
#define GIS3 3
#define A3 4
#define AIS3 5
#define H3 6
#define C4 7
#define CIS4 8
#define D4 9
#define DIS4 10
#define E4 11
#define F4 12
#define FIS4 13
#define G4 14
#define GIS4 15
#define A4 16
#define AIS4 17
#define H4 18
#define C5 19
#define CIS5 20
#define D5 21
#define DIS5 22
#define E5 23
#define F5 24
#define FIS5 25
#define G5 26
#define GIS5 27
#define A5 28
#define AIS5 29
#define H5 30
#define C6 31

class Shifts {
public:
  Shifts(int dSym, int dAsym, int whiteToBlack) {
    //init based on keyboard drawing
    shifts[F3] = 0;
    shifts[FIS3] = shifts[F3] + whiteToBlack;
    shifts[G3] = dAsym;
    shifts[GIS3] = shifts[G3] + whiteToBlack;
    shifts[A3] = dAsym + dSym;
    shifts[AIS3] = shifts[A3] + whiteToBlack;
    shifts[H3] = dAsym * 2 + dSym;
    shifts[C4] = 4 * dSym;
    shifts[CIS4] = shifts[C4] + whiteToBlack;
    shifts[D4] = shifts[C4] + dAsym;
    shifts[DIS4] = shifts[D4] + whiteToBlack;
    shifts[E4] = shifts[C4] + 2 * dAsym;

    initRestOfShifts(dSym);
  }

  int getShift(char key) {
    //TODO error checking
    return shifts[key];
  }
  
  static bool isBlack(char key){
    key = key%12;
    switch(key){
      case FIS3:
      case GIS3:
      case AIS3:
      case CIS4:
      case DIS4:
      return true;
    }
    return false;
  }

private:
  int shifts[32];

  void initRestOfShifts(int dSym) {
    //12 - total keys per octave
    //7  - white keys per octave
    for (int j = 1; j <= 2; j++) {
      for (int i = 0; i<12; i++) {
        shifts[F3 + 12 * j + i] = shifts[F3 + i] + 7 * j*dSym;

        if (12 * j + i == C6) //last key check
          return;
      }
    }
  }
};





