#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void saveGame() {

	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	fwrite(&cookies, sizeof(u64), 1, fp);
	fwrite(buildingData, sizeof(u64), 8, fp);
	fwrite(upgradeData, sizeof(u64), 4, fp);
	fclose(fp);
	
}

void moveCursor() {

	if (hidKeysDown() & KEY_DOWN) {
		cursor++;
	} else if (hidKeysDown() & KEY_UP) {
		cursor--;
	}
}

void resetCursor(int min, int max) {
	if (cursor > max) {
		cursor = max;
	} else if (cursor < min) {
		cursor = min;
	}
}