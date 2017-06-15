#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void saveGame() {

	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	fwrite(&cookies, sizeof(u64), 1, fp);
	fwrite(buildingTotal, sizeof(u64), 4, fp);
	fwrite(buildingCost, sizeof(u64), 4, fp);
	fwrite(upgradeCost, sizeof(u64), 5, fp);
	fwrite(upgradeTotal, sizeof(u64), 5, fp);
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

void addCookies() {
	cookies = cookies + (buildingTotal[0] * upgradeTotal[1]);
	cookies = cookies + ((buildingTotal[1] * 5) * upgradeTotal[2]);
	cookies = cookies + buildingTotal[2] * 15;
	
	
}

void loadGame() {
	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	if(!fp) { 
		fp = fopen("/3ds/data/cookiecollector/user.txt", "w+");
	}

    fread(&cookies, sizeof(u64), 1, fp);
	fread(buildingTotal, sizeof(u64), 4, fp);
	fread(buildingCost, sizeof(u64), 4, fp);
	fread(upgradeCost, sizeof(u64), 5, fp);
	fread(upgradeTotal, sizeof(u64), 5, fp);
	rewind(fp);
}

void makeSale(u64* increment, u64* cost) {
    if (cookies >= *cost) {
        cookies -= *cost;
        *cost *= 1.2;
        *increment += 1;
    }
    
}