#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

int cookies = 0;
int cookieM = 1;
int check = 0;
int cookieMCost = 100;
int clickCost = 10;
int grandmaCost = 100;
int bakeryCost = 1000;
int clickers = 0;
int grandmas = 0;
int bakeries = 0;

int main()
{
	gfxInitDefault();
	
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	consoleSelect(&topScreen);

	;printf("Hello, this is a cookie tapper app, by @Kaisogen!\n\n");
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
		if(kDown & KEY_B){
			printf("\n\n\n Hey there! Welcome to Cookie Collector! Thanks for opening the advanced explanation!");
			printf("\nIf you press A, you get your cookie production added to your total cookies!");
			printf("\nIf you press Up on the D-Pad, you can buy a clicker for a certain amount of cookies. This adds 0.1 cookies to your total cookies produced per click.");
			printf("\nPress Right on the D-Pad for Bakeries. They add 100!");
			printf("\nPress Left to hire a grandma. They give you one extra cookie (;");
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
				cookieM = cookieM + 0.1;
				clickers++;
			} else {
				printf("You don't have enough cookies to buy a clicker!\n");
				printf("You need %d more cookies!\n", clickCost - cookies);
			}
		}
		
		//Buy grandma
		if( kDown & KEY_LEFT){
			if(cookies >= grandmaCost){
				cookies-=grandmaCost;
				cookieM++;
				grandmaCost = grandmaCost * 1.5;
				grandmas++;
			} else {
				printf("You don't have enough cookies to hire a grandma!\n");
				printf("You need %d more cookies!\n", grandmaCost - cookies);
			}
		}
		
		if(kDown & KEY_RIGHT){
			if(cookies >= bakeryCost){
				cookies-=bakeryCost;
				cookieM+=100;
				bakeryCost = bakeryCost * 1.5;
				bakeries++;
			} else {
				printf("You don't have enough cookies to construct a bakery!\n");
				printf("You need %d more cookies!\n", bakeryCost - cookies);
			}
		}
		
		//Version Revisions
		if (kDown & KEY_X){
			printf("V.1.2: \n    1. Removed the cookie multiplier! \n    2. Added new ways to get more cookies!\n    Press Up to get a clicker, left to hire a grandma, and right to build a factory!\n    3. Statistics are now displayed on the bottomscreen, info on top!");
		}	
		
		consoleSelect(&bottomScreen);
		consoleClear();
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
	return 0;
}
