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

class Shifths{
public:
	Shifths(int dSym, int dAsym, int whiteToBlack){
		#init based on keyboard drawing
		shfts[KEY_F3] = 0;
		shfts[KEY_FIS3] = shfts[KEY_F3] + whiteToBlack;
		shfts[KEY_G3] = dAsym;
		shfts[KEY_GIS3] = shfts[KEY_G3] + whiteToBlack;
		shfts[KEY_A3] = dAsym+dSym;
		shfts[KEY_AIS3] = shfts[KEY_A3] + whiteToBlack;
		shfts[KEY_H3] = dAsym*2+dSym;
		shfts[KEY_C4] = 4*dSym;
		shfts[KEY_CIS4] = shfts[KEY_C4] + whiteToBlack;
		shfts[KEY_D4] = shfts[KEY_C4] + dAsym;
		shfts[KEY_DIS4] = shfts[KEY_D4] + whiteToBlack
		shfts[KEY_E4] = shfts[KEY_C4] + 2*dAsym;
		
		initRestOfShifts(dSym);
	}
	
	int getShift(byte key){
		//TODO error checking
		return shifts[key];
	}
	
private:
	int shfts [32];
	
	void initRestOfShifts(int dSym){
		//12 - total keys per octave
		//7  - white keys per octave
		for (int j=1;j<=2;j++){
			for (int i=0;i<12;i++){
				shfts[KEY_F3 + 12*j +i] = shfts[KEY_F3 + i] + 7*j*dSym;
				
				if (12*j +i == KEY_C5) //last key check
					return;
			}
		}
	}
}





