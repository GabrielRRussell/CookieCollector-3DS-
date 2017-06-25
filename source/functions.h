#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

extern u64 cookies;
extern u64 buildingTotal[4];
extern u64 buildingCost[4];
extern u64 upgradeTotal[6];
extern u64 upgradeCost[6];
extern int cursor;
extern int screen;
extern int version;

void saveGame();
void loadGame();
void moveCursor();
void resetCursor(int min, int max);
void addCookies();
void makeSale(u64* increment, u64* cost);
void printStatement(char* name, u64 cost, int place);
void resetScreen();
void switchScreen();

#endif