// This game was commented and made for those who don't understand C or 3DS Homebrew
#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

extern u64 cookies = 0;
int screen = 0;
extern int cursor = 0;

// Keep track of values

extern u64 buildingTotal[4] = {0};
extern u64 buildingCost[4] = {0};
extern u64 upgradeTotal[5] = {0};
extern u64 upgradeCost[5] = {0};


//Framerate Check
int frames = 0; 
int longTimer = 0;

int main()
{

	buildingTotal[0] = 0;
	buildingTotal[1] = 0;
	buildingTotal[2] = 0;
	buildingTotal[3] = 0;
	
	buildingCost[0] = 10;
	buildingCost[1] = 100;
	buildingCost[2] = 1000;
	buildingCost[3] = 5000;
	
	upgradeTotal[0] = 1;
	upgradeTotal[1] = 1;
	upgradeTotal[2] = 1;
	upgradeTotal[3] = 1;
	upgradeTotal[4] = 1;
	
	upgradeCost[0] = 10000;
	upgradeCost[1] = 100;
	upgradeCost[2] = 5000;
	upgradeCost[3] = 10000;
	upgradeCost[4] = 75000;
	
	
	
	gfxInitDefault();
	//Select Screens
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	//Choose which screen to print to (top)
	consoleSelect(&topScreen);


	//Open file user.txt as "fp". If it exists, read it. If it doesn't, create a new file.
	loadGame();
	
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Leave App
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu
		
		
		if (screen == 0) { //Select Which  Screen to Use

			consoleSelect(&topScreen);

			// Title Screen
			printf("\x1b[1;14H\x1b[47;30mCookie Collector 3DS\x1b[0m\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________");
			printf("\x1b[8;2HIt costs %llu cookies to build a clicker \e[K\n", buildingCost[0]);
			printf("\x1b[9;2HIt costs %llu cookies to hire a grandma \e[K\n", buildingCost[1]);
			printf("\x1b[10;2HIt costs %llu cookies to build a bakery\e[K\n", buildingCost[3]);
			
			moveCursor();
	
			//Add Cookies	
			if (kDown & KEY_X){
				cookies = cookies + upgradeTotal[0];
			} 
			
			if (kDown & KEY_A & cursor == 1) {
				screen = 1;
				cursor = 0;
				consoleClear();
			} else if (kDown & KEY_A & (cursor == 2)) {
				screen = 2;
				cursor = 0;
				consoleClear();
			}
			
			
			if (cursor == 1 & screen == 0) {
				printf("\x1b[12;2H\x1b[40;33m>\x1b[0m Shop\e[K\n");
				printf("\x1b[13;2H  Options\e[K\n");
			} else if (cursor == 2 & screen == 0) {
				printf("\x1b[12;2H  Shop\e[K\n");
				printf("\x1b[13;2H\x1b[40;33m>\x1b[0m Options\e[K\n");
			}
			
			
			resetCursor(1, 2);
			
		
		} else if (screen == 1) { //Select Shop
			
			consoleSelect(&topScreen);
			
			printf("\x1b[1;23HShop\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________\e[K\n");
			printf("\x1b[8;0HPress B to go back\e[K\n");
			
			if (cursor > 4 & (buildingTotal[0] <= 25)) {
				cursor = 4;
			} else if (cursor > 5) {
				cursor = 5;
			} else if (cursor < 1) {
				cursor = 1;
			}
			
			moveCursor();
			
			if (cursor == 1) {
				printf("\x1b[10;2H\x1b[40;33m>\x1b[0m Clicker:         %llu\e[K\n", buildingCost[0]);
				printf("\x1b[11;2H  Grandma:         %llu\e[K\n", buildingCost[1]);
				printf("\x1b[12;2H  Bakery:          %llu\e[K\n", buildingCost[2]);
				printf("\x1b[14;2H  Cookie Upgrade:  %llu\e[K\n", upgradeCost[0]);
				printf("\x1b[15;2H  Upgrade Clicker: %llu\e[K\n", upgradeCost[1]);
			} else if (cursor == 2) {
				printf("\x1b[10;2H  Clicker:         %llu\e[K\n", buildingCost[0]);
				printf("\x1b[11;2H\x1b[40;33m>\x1b[0m Grandma:         %llu\e[K\n", buildingCost[1]);
				printf("\x1b[12;2H  Bakery:          %llu\e[K\n", buildingCost[2]);
				printf("\x1b[14;2H  Cookie Upgrade:  %llu\e[K\n", upgradeCost[0]);
				printf("\x1b[15;2H  Upgrade Clicker: %llu\e[K\n", upgradeCost[1]);
				
			} else if (cursor == 3) {
				printf("\x1b[10;2H  Clicker:         %llu\e[K\n", buildingCost[0]);
				printf("\x1b[11;2H  Grandma:         %llu\e[K\n", buildingCost[1]);
				printf("\x1b[12;2H\x1b[40;33m>\x1b[0m Bakery:          %llu\e[K\n", buildingCost[2]);
				printf("\x1b[14;2H  Cookie Upgrade:  %llu\e[K\n", upgradeCost[0]);
				printf("\x1b[15;2H  Upgrade Clicker: %llu\e[K\n", upgradeCost[1]);
				
				
			} else if (cursor== 4) {
				printf("\x1b[10;2H  Clicker:         %llu\e[K\n", buildingCost[0]);
				printf("\x1b[11;2H  Grandma:         %llu\e[K\n", buildingCost[1]);
				printf("\x1b[12;2H  Bakery:          %llu\e[K\n", buildingCost[2]);
				printf("\x1b[14;2H\x1b[40;33m>\x1b[0m Cookie Upgrade:  %llu\e[K\n", upgradeCost[0]);
				printf("\x1b[15;2H  Upgrade Clicker: %llu\e[K\n", upgradeCost[1]);
			} else if (cursor == 5) {
				printf("\x1b[10;2H  Clicker:         %llu\e[K\n", buildingCost[0]);
				printf("\x1b[11;2H  Grandma:         %llu\e[K\n", buildingCost[1]);
				printf("\x1b[12;2H  Bakery:          %llu\e[K\n", buildingCost[2]);
				printf("\x1b[14;2H  Cookie Upgrade:  %llu\e[K\n", upgradeCost[0]);
				printf("\x1b[15;2H\x1b[40;33m>\x1b[0m Upgrade Clicker: %llu\e[K\n", upgradeCost[1]);
			}
			
			
			if (kDown & KEY_B) {
				screen = 0;
				cursor = 0;
				consoleClear();
			}
			
					//Buy clicker	
			if (cursor == 1 & (kDown & KEY_A)){
			
				if(cookies >= buildingCost[0]){
					cookies-=buildingCost[0];
					buildingCost[0] = buildingCost[0] * 1.2;
					buildingTotal[0]++;
				}
			}
		
			//Buy grandma
			if(cursor == 2 & (kDown & KEY_A)){
				makeSale(buildingTotal[1], buildingCost[1]);
			}
			//Buy Bakery
			if(kDown & KEY_A & cursor == 3){
				if(cookies >= buildingCost[2]){
					cookies-=buildingCost[2];
					buildingCost[2] = buildingCost[2] * 1.2;
					buildingTotal[2]++;
				} 
			}
			//Upgrade cookie
			if(kDown & KEY_A & cursor == 4) {
				if(cookies >= upgradeCost[0]) {
					cookies-= upgradeCost[0];
					upgradeCost[0] = upgradeCost[0] * 1.2;
					upgradeTotal[0]++;
				}
			
			}
			//Upgrade Clicker
			if((kDown & KEY_A) & cursor == 5) {
				if(cookies >= upgradeCost[1]) {
					cookies-= upgradeCost[1];
					upgradeCost[1] = upgradeCost[1] * 1.2;
					upgradeTotal[1]++;
				}
			}
			//----------------------------------------------------
			//---------------------End Of-------------------------
			//---------------------Screen-------------------------
			//----------------------------------------------------
			
		} else if (screen == 2) {
		
			if (kDown & KEY_B) {
				screen = 0;
				cursor = 0;
				printf("\x1b[8;H          \e[K\n");
				printf("\x1b[11;0H        \e[K\n");
				consoleClear();
				
			}
			consoleSelect(&topScreen);
			printf("\x1b[1;23HConfig\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________\e[K\n");

			if (screen == 2){
				printf("\x1b[8;2HPress B to go back\e[K\n");
			}
			

			resetCursor(1, 2);

			moveCursor();
			
			if (cursor == 1 & screen == 2) {
				printf("\x1b[12;2H\x1b[40;33m>\x1b[m Save\e[K\n");
				printf("\x1b[13;2H  Reset\e[K\n");
			} else if (cursor == 2 & screen == 2) {
				printf("\x1b[12;2H  Save\e[K\n");
				printf("\x1b[13;2H\x1b[43;31m> Reset (THIS CANNOT BE UNDONE)\x1b[0m\e[K\n");
			}
			
			if ((cursor == 1) & kDown & KEY_A) {
				saveGame();
			} else if ((cursor == 2) & kDown & KEY_A) {
				cookies = 0;
				buildingTotal[0] = 0;
				buildingTotal[1] = 0;
				buildingTotal[2] = 0;
				buildingTotal[3] = 0;
	
				buildingCost[0] = 10;
				buildingCost[1] = 100;
				buildingCost[2] = 1000;
				buildingCost[3] = 5000;
	
				upgradeTotal[0] = 1;
				upgradeTotal[1] = 1;
				upgradeTotal[2] = 1;
				upgradeTotal[3] = 1;
	
				upgradeCost[0] = 100;
				upgradeCost[1] = 5000;
				upgradeCost[2] = 10000;
				upgradeCost[3] = 75000;
				saveGame();
			}
			
			
		}
		
			consoleSelect(&bottomScreen);
		
			//%d is a replacement for an integer
			printf("\x1b[1;1HPress X to gain %llu cookies!\e[K\n", upgradeTotal[0]);
			printf("\x1b[3;1HYou have %llu clickers so far! (x%llu)\e[K\n", buildingTotal[0], upgradeTotal[1]);
			printf("\x1b[4;1HYou have %llu grandmas hired so far!\e[K\n", buildingTotal[1]);
			printf("\x1b[5;1HYou have %llu bakeries built so far!\e[K\n", buildingTotal[2]);
			printf("\x1b[8;1HAuthor: Kaisogen");
			printf("\x1b[9;1HPress /\\ or \\/ to select");
		
		
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		
		frames++;
		longTimer++;
		
		if (frames % 60 == 0) 
		{
			addCookies();
			frames = 0;
			
		}
		
		
		if (longTimer == 900) {
			FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
		
			saveGame();
			consoleClear();
			longTimer = 0;
		
		} else if (longTimer >= 840) {
			printf("\x1b[12;1H\x1b[43;31mAutosaving, don't quit.\x1b[0m\e[K\n");
		}
		
	}
	gfxExit();
	return 0; //Program exited properly
}
