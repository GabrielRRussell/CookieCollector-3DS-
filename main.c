// This game was commented and made for those who don't understand C or 3DS Homebrew
#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

u64 cookies = 0;
int cookieM = 1; //Multiplier
int screen = 0;
int cursor = 12;

// Keep track of values

u64 buildingData[6] = {0};

//Framerate Check
int frames = 0; 

int main()
{

	buildingData[3] = 10;
	buildingData[4] = 100;
	buildingData[5] = 1000;

	gfxInitDefault();
	//Select Screens
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	//Choose which screen to print to (top)
	consoleSelect(&topScreen);


	//Open file user.txt as "fp". If it exists, read it. If it doesn't, create a new file.
	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	if(!fp) { 
		fp = fopen("/3ds/data/cookiecollector/user.txt", "w+");
	}
	
	//Write data from file to variables.
    fread(&cookies, sizeof(u64), 1, fp);
	fread(buildingData, sizeof(u64), 5, fp);
	rewind(fp);
	
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Leave App
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu
		
		
		if (screen == 0) { //Select Which Screen to Use

			consoleSelect(&topScreen);

			// Title Screen
			printf("\x1b[1;14HCookie Collector 3DS\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________");
			printf("\x1b[8;2HIt costs %llu cookies to build a clicker\e[K\n", buildingData[3]);
			printf("\x1b[9;2HIt costs %llu cookies to hire a grandma\e[K\n", buildingData[4]);
			printf("\x1b[10;2HIt costs %llu cookies to build a bakery\e[K\n", buildingData[5]);
			
		
	
			//Add Cookies	
			if (kDown & KEY_X){
				cookies = cookies + cookieM;
			} 
			
			if (kDown & KEY_A & cursor == 12) {
				screen = 1;
				cursor = 0;
				consoleClear();
			}
			
			if (hidKeysDown() & KEY_SELECT) {
				fwrite(&cookies, sizeof(u64), 1, fp);
				fwrite(buildingData, sizeof(u64), 5, fp);
				fclose(fp);
			}
			
			if (kDown & KEY_DOWN) {
				cursor++;
			} else if (kDown & KEY_UP) {
				cursor--;
			}
			
			if (cursor == 12 & screen == 0) {
				printf("\x1b[12;3H> Shop\e[K\n");
				printf("\x1b[13;3H  Config\e[K\n");
			} else if (cursor == 13 & screen == 0) {
				printf("\x1b[12;3H  Shop\e[K\n");
				printf("\x1b[13;3H> Config\e[K\n");
			}
			
			
			if (cursor < 12) {
				cursor = 12;
			} else if (cursor > 13) {
				cursor = 13;
			}
			
			
		
			consoleSelect(&bottomScreen);
		
			//%d is a replacement for an integer
			printf("\x1b[1;1HPress X to gain %d cookies!\e[K\n", cookieM);
			printf("\x1b[3;1HYou have %llu clickers so far!\e[K\n", buildingData[0]);
			printf("\x1b[4;1HYou have %llu grandmas hired so far!\e[K\n", buildingData[1]);
			printf("\x1b[5;1HYou have %llu bakeries built so far!\e[K\n", buildingData[2]);
			printf("\x1b[8;1HAuthor: Kaisogen");
			printf("\x1b[9;1HPress /\\ or \\/ to select");
			printf("\x1b[10;1HPress Select to Save");
		
		} else if (screen == 1) { //Select Shop
			
			consoleSelect(&topScreen);
			
			printf("\x1b[1;23HShop\e[K\n");
			printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
			printf("\x1b[6;0H__________________________________________________\e[K\n");
			printf("\x1b[8;0HPress B to go back\e[K\n");
			
			if (cursor > 12) {
				cursor = 12;
			} else if (cursor < 10) {
				cursor = 10;
			}
			
			if (kDown & KEY_DOWN) {
				cursor++;
			} else if (kDown & KEY_UP) {
				cursor--;
			}
			
			if (cursor == 10) {
				printf("\x1b[10;2H> Clicker: %llu\e[K\n", buildingData[3]);
				printf("\x1b[11;2H  Grandma: %llu\e[K\n", buildingData[4]);
				printf("\x1b[12;2H  Bakery: %llu\e[K\n", buildingData[5]);
			} else if (cursor == 11) {
				printf("\x1b[10;2H  Clicker: %llu\e[K\n", buildingData[3]);
				printf("\x1b[11;2H> Grandma: %llu\e[K\n", buildingData[4]);
				printf("\x1b[12;2H  Bakery: %llu\e[K\n", buildingData[5]);
			} else if (cursor == 12) {
				printf("\x1b[10;2H  Clicker: %llu\e[K\n", buildingData[3]);
				printf("\x1b[11;2H  Grandma: %llu\e[K\n", buildingData[4]);
				printf("\x1b[12;2H> Bakery: %llu\e[K\n", buildingData[5]);
			}
			
			
			if (kDown & KEY_B) {
				screen = 0;
				cursor = 0;
				consoleClear();
			}
			
					//Buy clicker	
			if (cursor == 10 & kDown & KEY_A){
			
				if(cookies >= buildingData[3]){
					cookies-=buildingData[3];
					buildingData[3] = buildingData[3] * 1.2;
					buildingData[0]++;
				}
			}
		
			//Buy grandma
			if(cursor == 11 & kDown * KEY_A){
				if(cookies >= buildingData[4]){
					cookies-=buildingData[4];
					buildingData[4] = buildingData[4] * 1.2;
					buildingData[1]++;
				}
			}
		
			if(kDown & KEY_A & cursor == 12){
				if(cookies >= buildingData[5]){
					cookies-=buildingData[5];
					buildingData[5] = buildingData[5] * 1.2;
					buildingData[2]++;
				} 
			}
			
			
			
		}
		
		
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		
		frames++;
		
		if (frames % 60 == 0) 
		{
			cookies = cookies + buildingData[0];
			
			cookies = cookies + buildingData[1] * 5;
			
			cookies = cookies + buildingData[2] * 15;
			
			frames = 0;
			
		}
		
		
	}
	gfxExit();
	return 0; //Program exited properly
}
