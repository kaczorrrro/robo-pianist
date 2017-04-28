/*
Creates array with number of engine steps required for each key
Written by Sebastian Kaczor
*/
#pragma once

#define KEY_F3 0
#define KEY_FIS3 1
#define KEY_G3 2
#define KEY_GIS3 3
#define KEY_A3 4
#define KEY_AIS3 5
#define KEY_H3 6
#define KEY_C4 7
#define KEY_CIS4 8
#define KEY_D4 9
#define KEY_DIS4 10
#define KEY_E4 11
#define KEY_F4 12
#define KEY_FIS4 13
#define KEY_G4 14
#define KEY_GIS4 15
#define KEY_A4 16
#define KEY_AIS4 17
#define KEY_H4 18
#define KEY_C5 19
#define KEY_CIS5 20
#define KEY_D5 21
#define KEY_DIS5 22
#define KEY_E5 23
#define KEY_F5 24
#define KEY_FIS5 25
#define KEY_G5 26
#define KEY_GIS5 27
#define KEY_A5 28
#define KEY_AIS5 29
#define KEY_H5 30
#define KEY_C5 31

class Shifths {
public:
	Shifths(int dSym, int dAsym, int whiteToBlack) {
		//init based on keyboard drawing
		shifts[KEY_F3] = 0;
		shifts[KEY_FIS3] = shifts[KEY_F3] + whiteToBlack;
		shifts[KEY_G3] = dAsym;
		shifts[KEY_GIS3] = shifts[KEY_G3] + whiteToBlack;
		shifts[KEY_A3] = dAsym + dSym;
		shifts[KEY_AIS3] = shifts[KEY_A3] + whiteToBlack;
		shifts[KEY_H3] = dAsym * 2 + dSym;
		shifts[KEY_C4] = 4 * dSym;
		shifts[KEY_CIS4] = shifts[KEY_C4] + whiteToBlack;
		shifts[KEY_D4] = shifts[KEY_C4] + dAsym;
		shifts[KEY_DIS4] = shifts[KEY_D4] + whiteToBlack;
		shifts[KEY_E4] = shifts[KEY_C4] + 2 * dAsym;

		initRestOfShifts(dSym);
	}

	int getShift(char key) {
		//TODO error checking
		return shifts[key];
	}

private:
	int shifts[32];

	void initRestOfShifts(int dSym) {
		//12 - total keys per octave
		//7  - white keys per octave
		for (int j = 1; j <= 2; j++) {
			for (int i = 0; i<12; i++) {
				shifts[KEY_F3 + 12 * j + i] = shifts[KEY_F3 + i] + 7 * j*dSym;

				if (12 * j + i == KEY_C5) //last key check
					return;
			}
		}
	}
};





