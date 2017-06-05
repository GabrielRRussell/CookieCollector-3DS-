// This game was commented and made for those who don't understand C or 3DS Homebrew
#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

u64 cookies = 0;
int cookieM = 1; //Multiplier
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

	FILE * fp = fopen("/3ds/data/cookiecollector/user.txt", "r+");
	
	if(!fp) { 
		fp = fopen("/3ds/data/cookiecollector/user.txt", "w+");
	}
	
    fread(&cookies, sizeof(u64), 1, fp);
	fread(buildingData, sizeof(u64), 5, fp);
	rewind(fp);
	
	// Main loop
	while (aptMainLoop())
	{
		consoleSelect(&topScreen);
		gspWaitForVBlank();
		hidScanInput();

		//Leave App
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu
		
		
		
		// Title Screen
		printf("\x1b[1;14HCookie Collector 3DS");
		printf("\x1b[5;15HYou have: %lld cookies \e[K\n", cookies);
		printf("\x1b[6;0H__________________________________________________");
		printf("\x1b[8;2HIt costs %llu cookies to build a clicker\e[K\n", buildingData[3]);
		printf("\x1b[9;2HIt costs %llu cookies to hire a grandma\e[K\n", buildingData[4]);
		printf("\x1b[10;2HIt costs %llu cookies to build a bakery\e[K\n", buildingData[5]);
		
		
		
	
		//Add Cookies	
		if (kDown & KEY_A){
			cookies = cookies + cookieM;
		}
			
		//Buy clicker	
		if (kDown & KEY_UP){
			
			if(cookies >= buildingData[3]){
				cookies-=buildingData[3];
				buildingData[3] = buildingData[3] * 1.2;
				buildingData[0]++;
			}
		}
		
		//Buy grandma
		if( kDown & KEY_LEFT){
			if(cookies >= buildingData[4]){
				cookies-=buildingData[4];
				buildingData[4] = buildingData[4] * 1.2;
				buildingData[1]++;
			}
		}
		
		if(kDown & KEY_RIGHT){
			if(cookies >= buildingData[5]){
				cookies-=buildingData[5];
				buildingData[5] = buildingData[5] * 1.2;
				buildingData[2]++;
			} 
		}

       
		if (hidKeysDown() & KEY_SELECT) {
            fwrite(&cookies, sizeof(u64), 1, fp);
			fwrite(buildingData, sizeof(u64), 5, fp);
            fclose(fp);
        }
		
		consoleSelect(&bottomScreen);

		frames++;
		
		if (frames % 60 == 0) 
		{
			cookies = cookies + buildingData[0];
			
			cookies = cookies + buildingData[1] * 5;
			
			cookies = cookies + buildingData[2] * 15;
			
			frames = 0;
			
		}
		
		//%d is a replacement for an integer
		printf("\x1b[1;1HYou gain %d cookies per click!\e[K\n", cookieM);
		printf("\x1b[3;1HYou have %llu clickers so far!\e[K\n", buildingData[0]);
		printf("\x1b[4;1HYou have %llu grandmas hired so far!\e[K\n", buildingData[1]);
		printf("\x1b[5;1HYou have %llu bakeries built so far!\e[K\n", buildingData[2]);
		
		printf("\x1b[7;1HPress /\\ to buy a clicker");
		printf("\x1b[8;1HPress <- to hire a grandma");
		printf("\x1b[9;1HPress -> to produce a factory");
		printf("\x1b[10;1HPress Select to Save");
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		
	}
	gfxExit();
	return 0; //Program exited properly
}
