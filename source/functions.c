#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <sys/stat.h> 
#include <sys/types.h> 

void saveGame() {

	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	mkdir("/3ds/data/", 0777);
	mkdir("/3ds/data/CookieCollector/", 0777);
	
	fwrite(&version, sizeof(int), 1, fp);
	fwrite(&cookies, sizeof(u64), 1, fp);
	fwrite(buildingTotal, sizeof(u64), 4, fp);
	fwrite(buildingCost, sizeof(u64), 4, fp);
	fwrite(upgradeCost, sizeof(u64), 6, fp);
	fwrite(upgradeTotal, sizeof(u64), 6, fp);
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
	cookies = cookies + buildingTotal[3] * 50;
}

void loadGame() {
	mkdir("/3ds/data/", 0777);
	mkdir("/3ds/data/CookieCollector/", 0777);
	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	if(!fp) { 
		fp = fopen("/3ds/data/cookiecollector/user.txt", "w+");
	}
	
	fread(&version, sizeof(int), 1, fp);
	
	if (version == 170) {
		fread(&cookies, sizeof(u64), 1, fp);
		fread(buildingTotal, sizeof(u64), 4, fp);
		fread(buildingCost, sizeof(u64), 4, fp);
		fread(upgradeCost, sizeof(u64), 6, fp);
		fread(upgradeTotal, sizeof(u64), 6, fp);
		rewind(fp);
	}
}

void makeSale(u64* increment, u64* cost) {
    if (cookies >= *cost) {
        cookies -= *cost;
        *cost *= 1.2;
        *increment += 1;
    }
    
}

void printStatement(char* name, u64 cost, int place) {
		
	if (cursor == place) {
		printf("\x1b[%d;2H\x1b[40;33m> \x1b[0m%s: %llu\e[K\n", place, name, cost);
	} else {
		printf("\x1b[%d;2H  %s: %llu\e[K\n", place, name, cost);
	}
}

			
void resetScreen() {
	if (hidKeysDown() & KEY_B) {
		screen = 0;
		cursor = 0;
		printf("\x1b[8;0H                   \e[K\n");
		printf("\x1b[9;0H                   \e[K\n");
		printf("\x1b[10;0H                   \e[K\n");
		printf("\x1b[11;0H                   \e[K\n");
		printf("\x1b[12;0H                   \e[K\n");
		printf("\x1b[13;0H                   \e[K\n");
		printf("\x1b[14;0H                   \e[K\n");
		printf("\x1b[15;0H                   \e[K\n");
		printf("\x1b[16;0H                   \e[K\n");
		printf("\x1b[17;0H                   \e[K\n");
		printf("\x1b[18;0H                   \e[K\n");
		printf("\x1b[19;0H                   \e[K\n");

		
		consoleClear();			
	}
}
