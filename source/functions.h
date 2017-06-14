#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

extern u64 cookies;
extern u64 buildingData[10];
extern u64 upgradeData[4];
extern int cursor;

void saveGame();
void moveCursor();
void resetCursor(int min, int max);


#endif