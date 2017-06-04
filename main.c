// This game was commented and made for those who don't understand C or 3DS Homebrew
#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

int cookies = 0;
int cookieM = 1; //Multiplier
int check = 0;
int cookieMCost = 100; //Multiplier Cost
int clickCost = 10; //Automatic Cost
int grandmaCost = 100; //Automatic Cost
int bakeryCost = 1000; //Automatic Cost

// Keep track of values
int clickers = 0;
int grandmas = 0;
int bakeries = 0;

//Framerate Check
int frames = 0; 

int main()
{
	gfxInitDefault();
	//Select Screens
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	//Choose which screen to print to (top)
	consoleSelect(&topScreen);

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
		printf("\x1b[5;2HYou have: %d cookies", cookies);
		printf("\x1b[6;0H__________________________________________________");
		printf("\x1b[8;2HIt costs %d cookies to build a clicker", clickCost);
		printf("\x1b[9;2HIt costs %d cookies to hire a grandma", grandmaCost);
		printf("\x1b[10;2HIt costs %d cookies to build a bakery", bakeryCost);
		
		
		
	
		//Add Cookies	
		if (kDown & KEY_A){
			cookies = cookies + cookieM;
			check = 1;
		}
			
		//Buy clicker	
		if (kDown & KEY_UP){
			
			if(cookies > clickCost){
				cookies-=clickCost;
				clickCost = clickCost * 1.5;
				clickers++;
			}
		}
		
		//Buy grandma
		if( kDown & KEY_LEFT){
			if(cookies >= grandmaCost){
				cookies-=grandmaCost;
				grandmaCost = grandmaCost * 1.5;
				grandmas++;
			}
		}
		
		if(kDown & KEY_RIGHT){
			if(cookies >= bakeryCost){
				cookies-=bakeryCost;
				bakeryCost = bakeryCost * 1.5;
				bakeries++;
			} 
		}
		
		consoleSelect(&bottomScreen);

		frames++;
		
		if (frames % 60 == 0) 
		{
			cookies = cookies + clickers;
			
			cookies = cookies + grandmas * 2;
			
			frames = 0;
		}
		
		consoleClear();
		
		//%d is a replacement for an integer
		printf("\x1b[1;1HYou gain %d cookies per click!\n", cookieM);
		printf("\x1b[3;1HYou have %d clickers so far!\n", clickers);
		printf("\x1b[4;1HYou have %d grandmas hired so far!\n", grandmas);
		printf("\x1b[5;1HYou have %d bakeries built so far!\n", bakeries);
		
		printf("\x1b[7;1HPress /\\ to buy a clicker");
		printf("\x1b[8;1HPress <- to hire a grandma");
		printf("\x1b[9;1HPress -> to produce a factory");
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		

		
		
	}
	gfxExit();
	return 0; //Program exited properly
}
