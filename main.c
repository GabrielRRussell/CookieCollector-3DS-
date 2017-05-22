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

	;printf("Hello, this is a cookie tapper app, by @Kaisogen!\n\n"); //For some reason the code won't compile without this semicolon at the beginning.
	printf("Get more cookies by pressing A!\nFor a longer tutorial, press B!\n\n"); 
	printf("If you want to see bugfixes for the current version, press X!\n\n");
	printf("This is version 1.2!\n\n\n");
	

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
		
		//Tutorial!
		if(kDown & KEY_B){	//kDown is true when a key is held down.
			consoleClear();
			printf("\n\n\n Hey there! Welcome to Cookie Collector! Thanks for opening the advanced explanation!");
			printf("\nIf you press A, you get your cookie production added to your total cookies!");
			printf("\nIf you press Up on the D-Pad, you can buy a clicker for a certain amount of cookies. This adds 0.1 cookies to your total cookies produced per click.");
			printf("\nPress Right on the D-Pad for Bakeries. They add 100!");
			printf("\nPress Left to hire a grandma. They give you one extra cookie per second!");
			printf("Press the Home button if you ever want to leave!");
		}
		
	
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
			} else {
				consoleSelect(&bottomScreen);
				consoleClear();
				printf("You don't have enough cookies to buy a clicker!\n");
				printf("You need %d more cookies!\n", clickCost - cookies);
			}
		}
		
		//Buy grandma
		if( kDown & KEY_LEFT){
			if(cookies >= grandmaCost){
				cookies-=grandmaCost;
				grandmaCost = grandmaCost * 1.5;
				grandmas++;
			} else {
				consoleSelect(&bottomScreen);
				consoleClear();
				printf("You don't have enough cookies to hire a grandma!\n");
				printf("You need %d more cookies!\n", grandmaCost - cookies);
			}
		}
		
		if(kDown & KEY_RIGHT){
			if(cookies >= bakeryCost){
				cookies-=bakeryCost;
				bakeryCost = bakeryCost * 1.5;
				bakeries++;
			} else {
				consoleSelect(&bottomScreen);
				consoleClear();
				printf("You don't have enough cookies to construct a bakery!\n");
				printf("You need %d more cookies!\n", bakeryCost - cookies);
			}
		}
		
		//Version Revisions
		if (kDown & KEY_X){
			consoleClear();
			printf("V.1.2: \n    1. Removed the cookie multiplier! \n    2. Added new ways to get more cookies!\n    Press Up to get a clicker, left to hire a grandma, and right to build a factory!\n    3. Statistics are now displayed on the bottomscreen, info on top!");
		}	
		
		consoleSelect(&bottomScreen);
		//I couldn't get a timer working properly, so sorry for stealing your code, Machinumps! 
		//This timer checks if the remainder of the frames value, when divided by three, is zero. If the remainder is zero, it fires.
		//This should be firing every free times then.
		if (frames % 3 == 0) {
			consoleClear();
			cookies = cookies + (clickers * 1);
			cookies = cookies + (grandmas * 3);
			cookies = cookies + (factories * 10);
		}
		
		//Lazy reset frames. I haven't tested this code yet, so it might not work. I gave it three seconds before resetting.
		//(dev comment) Old internal revisions had it resetting at exactly three seconds. In case the timer missed the three second mark by just a little bit, I added a proper operation to avoid this.
		if (frames % 180 == 0) {
			frames = 0;	
		}
		
		//%d is a replacement for an integer
		printf("You have %d cookies!\n", cookies);
		printf("You gain %d cookies per round!\n", cookieM);
		printf("You have %d clickers so far!\n", clickers);
		printf("You have %d grandmas hired so far!\n", grandmas);
		printf("You have %d bakeries built so far!\n", bakeries);
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		

		
		
	}
	gfxExit();
	return 0; //Program exited properly
}
