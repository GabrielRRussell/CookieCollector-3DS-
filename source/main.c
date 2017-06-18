// This game was commented and made for those who don't understand C or 3DS Homebrew
#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

extern u64 cookies = 0;
extern int screen = 0;
extern int cursor = 0;
extern int version = 170;

// Keep track of values

extern u64 buildingTotal[4] = {0};
extern u64 buildingCost[4] = {0};
extern u64 upgradeTotal[6] = {0};
extern u64 upgradeCost[6] = {0};


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
	upgradeTotal[5] = 1;
	
	upgradeCost[0] = 10000;
	upgradeCost[1] = 50000;
	upgradeCost[2] = 25000;
	upgradeCost[3] = 50000;
	upgradeCost[4] = 75000;
	upgradeCost[5] = 100000;
	
	
	
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
			printf("\x1b[8;0HGithub Repo: Kaisogen/CookieCollector-3DS-");
			
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
			
			resetCursor(10, 16);
			moveCursor();
			resetScreen();
			
			if (screen == 1) {
			printStatement("Clicker", buildingCost[0], 10);
			printStatement("Grandma", buildingCost[1], 11);
			printStatement("Bakery", buildingCost[2], 12);
			printStatement("Bank", buildingCost[3], 13);
			printStatement("Cookie Upgrade", upgradeCost[0], 14);
			printStatement("Clicker Boost", upgradeCost[1], 15);
			printStatement("Grandma's Recipe", upgradeCost[2], 16);
			printStatement("Motivation Boost", upgradeCost[3], 17);
			printStatement("Anti-Inflation Cookies", upgradeCost[4], 18);
			};
			
			//Buy clicker	
			if ((cursor == 10) & (kDown & KEY_A)){
				makeSale(&buildingTotal[0], &buildingCost[0]);
			}
		
			//Buy grandma
			if((cursor == 11) & (kDown & KEY_A)){
				makeSale(&buildingTotal[1], &buildingCost[1]);
			}

			//Buy Bakery
			if(kDown & KEY_A & (cursor == 12)){
				makeSale(&buildingTotal[2], &buildingCost[2]);
			}
			//Buy Bank
			if(kDown & KEY_A & (cursor == 13)) {
				makeSale(&buildingTotal[3], &buildingCost[3]);			
			}
			//Cookie Upgrade
			if((kDown & KEY_A) & (cursor == 14)) {
				makeSale(&upgradeTotal[0], &upgradeCost[0]);
			}
			//Clicker Upgrade
			if((kDown & KEY_A) & (cursor == 15)) {
				makeSale(&upgradeTotal[1], &upgradeCost[1]);
			}
			//Grandma Upgrade
			if((kDown & KEY_A) & (cursor == 16)) {
				makeSale(&upgradeTotal[2], &upgradeCost[2]);
			} 
			//Bakery Upgrade
			if((kDown & KEY_A) & (cursor == 17)) {
				makeSale(&upgradeTotal[3], &upgradeCost[3]);
			}
			//Bank Upgrade
			if((kDown & KEY_A) & (cursor == 18)) {
				makeSale(&upgradeTotal[4], &upgradeCost[4]);
			}
			//----------------------------------------------------
			//---------------------End Of-------------------------
			//---------------------Screen-------------------------
			//----------------------------------------------------
			
		} else if (screen == 2) {
		
			resetScreen();
			consoleSelect(&topScreen);
			printf("\x1b[1;23HConfig\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________\e[K\n");

			if (screen == 2){
				printf("\x1b[8;2HPress B to go back\e[K\n");
			}
			

			resetCursor(1, 2);

			moveCursor();
			
			if ((cursor == 1) & (screen == 2)) {
				printf("\x1b[12;2H\x1b[40;33m>\x1b[m Save\e[K\n");
				printf("\x1b[13;2H  Reset\e[K\n");
			} else if ((cursor == 2) & (screen == 2)) {
				printf("\x1b[12;2H  Save\e[K\n");
				printf("\x1b[13;2H\x1b[43;31m> Reset (THIS CANNOT BE UNDONE)\x1b[0m\e[K\n");
			}
			
			if ((cursor == 1) & (kDown & KEY_A)) {
				saveGame();
			} else if ((cursor == 2) & (kDown & KEY_A)) {
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

				
			} else if ((cursor == 3) & (kDown & KEY_A)) {
			
				
			
			}
			
			
		} 
		
			consoleSelect(&bottomScreen);
		
			//%d is a replacement for an integer
			printf("\x1b[1;1HPress X to gain %llu cookies!\e[K\n", upgradeTotal[0]);
			printf("\x1b[3;1HClickers: %llu (x%llu)\e[K\n", buildingTotal[0], upgradeTotal[1]);
			printf("\x1b[4;1HGrandmas: %llu (x%llu)\e[K\n", buildingTotal[1], upgradeTotal[2]);
			printf("\x1b[5;1HBakeries: %llu (x%llu)\e[K\n", buildingTotal[2], upgradeTotal[3]);
			printf("\x1b[6;1HBanks:    %llu (x%llu)\e[K\n", buildingTotal[3], upgradeTotal[4]);
			printf("\x1b[28;1HAuthor: Kaisogen");
			printf("\x1b[29;1Hv1.7.0");
			printf("\x1b[8;1HPress /\\ or \\/ to select");
		
		
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		
		frames++;
		longTimer++;
		
		if (frames % 62 == 0) 
		{
			addCookies();
			
		}
		
		
		if ((longTimer == 907) & (version == 170)) {
			FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
		
			saveGame();
			consoleClear();
			longTimer = 0;
		
		} else if (longTimer >= 840 & (version == 170)) {
			printf("\x1b[12;1H\x1b[43;31mAutosaving, don't quit.\x1b[0m\e[K\n");
		} else {
		}
		
	}
	gfxExit();
	return 0; //Program exited properly
}
