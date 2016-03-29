#include <string.h>
#include <3ds.h>
#include <stdio.h>

int cookies = 0;
int cookieM = 1;
int check = 0;
int cookieMCost = 100;

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL) //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	;printf("Hello, this is a cookie tapper app, by @Kaisogen!\n\n");
	printf("If you ever want to leave, press Start!\n\n");
	printf("Press A to increase your cookies by one!\n\n");
	printf("If you have 100 cookies, press Y to upgrade!\n\n");
	printf("This is version 1.0!\n\n\n");

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Leave App
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu
		
	
		//Add Cookies	
		if (kDown & KEY_A){
			cookies = cookies + cookieM;
			check = 1;
		}
			
		//Buy cookie multiplier	
		if (kDown & KEY_Y){
			if(cookies >= 100){
				cookieM = cookieM * 2;
				cookies = cookies - cookieMCost;
				cookieMCost = cookieMCost * 1.5;
				printf("You have %d cookies left!", cookies);
			}
			else{
				printf("You don't have enough cookies!\n\n");
				printf("You need %d more cookies to buy an upgrade!", cookieMCost - cookies);
			}
		}	
		
			
		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		if(check == 1) {
			printf("You have %d cookies!\n", cookies);
			check = 0;
		}
		
	}

	gfxExit();
	return 0;
}